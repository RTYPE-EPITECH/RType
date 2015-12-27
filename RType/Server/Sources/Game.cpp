#include "Game.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Obstacle.hpp"
#include "Client.hpp"
#include "Missile.hpp"
#include <iostream>
#include "Client.hpp"
#include "MonsterFactory.hpp"
#include "WaveFactory.hpp"
#include "Tools.hpp"
#include "Network.hpp"

#ifdef _WIN32
# include "WTimer.hpp"
# include "WMutex.hpp"
#else
# include "UTimer.hpp"
# include "UMutex.hpp"
#endif

std::vector<size_t>		Game::_ids;

Game::Game(IConditionVariable * c)
{
_condVar = c;
	_currwave = 0;
	_stateScroll = 0;
	timer = NULL;
	mutex = NULL;
	_objs = NULL;
	_idThread = 0;
	if (_ids.size() > 0)
		_id = _ids.back() + 1;
	else
		_id = 1;
	std::string name("game-");
	name += Tools::NumberToString(_id) + ".log";
	_log = new Log(name);
	_log->addLog("[Game::Constructor] Object created");
}

Game::~Game()
{
	if (timer)
		delete(timer);
	if (mutex)
		delete(mutex);
	if (_objs)
		delete(_objs);
	if (_log)
		delete(_log);
}

bool Game::addClient(Client * cl)
{
	_log->addLog("[Game::addClient] Try to add client");
	if (getSizeAvailable() <= 0)
		{
			_log->addLog("[Game::addClient] Fail because not enought place");
			return false;
		}
	if (!cl->init(this))
	{
		_log->addLog("[Game::addClient] Fail because the client can't be initialized");
		return false;
	}
	mutex->lock();
	_clients.push_back(cl);
	mutex->unlock();
	cl->setState(BEGINNING);
	_log->addLog("[Game::addClient] Client added successfully");
	return true;
}

void Game::removeClient(Client * c)
{
	mutex->lock();
	for (std::vector<Client *>::iterator i = _clients.begin();
	i != _clients.end(); ++i)
		if ((*i)->getPlayer()->getId() == c->getPlayer()->getId())
		{
			(*i)->getPlayer()->die(this);
			_clients.erase(i);
			break;
		}
	mutex->unlock();
	_log->addLog("[Game::removeClient] Client properly destroyed");
}

size_t Game::getSizeAvailable() const
{
	mutex->lock();
	int size = MAX_PLAYER_GAME - _clients.size();
	mutex->unlock();
	if (size < 0)
		size = 0;
	return (size_t)size;
}

bool Game::init(const std::vector<std::string> & _lib)
{
	_log->addLog("[Game::init] Initialisation ...");
	/*// init Monsters Library AND create Init packet Cmd
	MonsterFactory * mf = MonsterFactory::getInstance();
	for (size_t i = 0; i < _lib.size(); i++)
		mf->addLibrary(_lib[i]);
	//std::vector<std::string> _monsters = mf->getAllMonsterName();
	//for (size_t i = 0; i < _monsters.size(); i++)*/
	_proto._addPositionPacket(SPAWN, 0, 59, 48, MONSTER, "Monster", "Monster");//_monsters[i].c_str(), _monsters[i].c_str());
	_proto._addPositionPacket(SPAWN, 0, 35, 18, PLAYER, "Player", "Player");
	_proto._addPositionPacket(SPAWN, 0, 48, 15, MISSILE, "Missile", "Missile");
	_proto._addPositionPacket(SPAWN, 0, 32, 32, OBSTACLE, "Obstacle", "Obstacle");
	_proto._putPositionPacketOnList();
	_initToClient.push_back(_proto._getLastPacket());

	// sample creation wave
	WaveFactory  wf;
	for (size_t i = 0; i < MAX_WAVES; i++)
	{
		wf.addObstacle();
		wf.addMonster();
		_waves.push_back(wf.getWaves());
	}


#ifdef _WIN32
	timer = new WTimer();
	mutex = new WMutex();
#else
	timer = new UTimer();
	mutex = new UMutex();
#endif
	if (!mutex->initialize())
		return false;
	_objs = _waves[_currwave];
	_log->addLog("[Game::init] initialized");
	return true;
}

bool Game::haveInput(unsigned long long t)
{
	bool check = false;
	mutex->lock();
	for (unsigned int i = 0; i < _clients.size(); i++)
		if (_clients[i]->haveInput())
		{
			check = true;
			break;
		}
	mutex->unlock();
	if (!check)
		_condVar->wait(t * 1000);
	return check;
}

bool Game::loop()
{
	long long tmp = 0;
	timer->start();
	_log->addLog("[Game::loop] loop begin");
  while (!isEnded())
    {
		if (_clients.size() == 0)
		{
			_log->addLog("[Game::loop] waiting for Clients");
			_condVar->wait();
			timer->start();
		}
		tmp = FPS * 100 - timer->getElapsedTimeInSec();
		if (tmp < 0)
			tmp = 0;
		if (haveInput(FPS * 100 - timer->getElapsedTimeInSec()))
		{
			_log->addLog("[Game::loop] There is input to handle");
		  mutex->lock();
		  // For each client, get the oldest Input
		  for (size_t i = 0; i < _clients.size(); i++)
			  if (POSITION_PACKET_SET == _clients[i]->getState())
			  {
				  const char * input = NULL;
				  if (!(input = _clients[i]->getInput()))
					  continue;
				  // set input into protocole to have the get/set
				  _proto._setNewPacket(input);
				  handleInputClient(_clients[i]);
				  _proto._putPositionPacketOnList();
				  _proto._setNewPacket(_proto._getLastPacket());
				  if (_proto._getArrayPositionLenght() > 0)
		  			addPacketForClients(_proto._getLastPacket(), true);
			  }
				// Client trying to connect
			  else
				  handleClientConnexion(_clients[i]);
		  mutex->unlock();
		  _log->addLog("[Game::loop] End of handle input");
		}

		// Check Scene :: Move Missile, Move scroll, Move enemies, Move Obstacles
		if (timer->getElapsedTimeInMicroSec() == FPS * 1000)
		{
			_log->addLog("[Game::loop] Timer OK for scrolling");
		  mutex->lock();
		  AllMove();
			_proto._putPositionPacketOnList();
		  _proto._setNewPacket(_proto._getLastPacket());
		if (_proto._getArrayPositionLenght() > 0)
		  		addPacketForClients(_proto._getLastPacket(), true);
		  mutex->unlock();
		  timer->start();
		  _log->addLog("[Game::loop] End of Scrolling");
		}
		monstersShoot();
		if (isWaveEnded())
		{
			_log->addLog("[Game::loop] Next wave ...");
			deleteWave();
			nextWave();
			_log->addLog("[Game::loop] Next wave OK");
		}
    }
  // PACKET GAME FINIE
  _log->addLog("[Game::loop] End of the loop");
  return true;
}

bool	Game::handleInputClient(Client * c)
{
  if (_proto._getHeaderOpcode() == 3)
    {
      ACTION a = (ACTION)_proto._getActionOpcode();
      Missile * m = NULL;
      _log->addLog(std::string("[Game::handleInputClient] Player " + Tools::NumberToString(c->getPlayer()->getId()) + " do an action "));
      if (a == SHOOT)
		{
		  if ((m = c->getPlayer()->shoot(this)) == NULL)
		  _log->addLog(std::string("[Game::handleInputClient] Player " + Tools::NumberToString(c->getPlayer()->getId()) + " cannot shoot"));
		}
      else
	if (c->getPlayer()->move(this, a, 1) == false)
	  _log->addLog(std::string("[Game::handleInputClient] Player " + Tools::NumberToString(c->getPlayer()->getId()) + " die"));
    }
  else if (_proto._getHeaderOpcode() == 5)
  {
	  _log->addLog("-----> PING PACKET RECEIVED");
		// Ping packet.
	  // ignore for now
  }
  else
    {
    	_log->addLog(std::string("[Game::handleInputClient] Player " + Tools::NumberToString(c->getPlayer()->getId()) + " sent an invalid packet"));
		_proto._createResponsePacket(INVALID_ACTION);
		c->addOutput(_proto._getLastPacket());
    }
  return true;
}

void		Game::handleClientConnexion(Client * c)
{
std::cout << "Game::handleClientConnexion" << std::endl;
	const char * input = c->getInput();
	if (input == NULL)
		return;
	_proto._setNewPacket(input);

	// CONNECT PACKET
	if (c->getState() == BEGINNING) {
		_log->addLog(std::string("[Game::handleClientConnexion] : state = BEGINNING"));
		if (_proto._getHeaderOpcode() == 1) {
			std::cout << "CONNECT PACKET" << std::endl;
			_log->addLog(std::string("[Game::HandleClientConnexion] : headerOpcode = 1"));
			c->protocole._createResponsePacket(NONE);
			c->addOutput(c->protocole._getLastPacket());
			c->setState(CONNECT_OK);
		}
	}

	// PARAMETER PACKET
	else if (c->getState() == CONNECT_OK) {
		_log->addLog(std::string("[Game::HandleClientConnexion] : state = CONNECT_OK"));
		if (_proto._getHeaderOpcode() == 2) {
			std::cout << "ID PACKET" << std::endl;
			_log->addLog(std::string("[Game::HandleClientConnexion] : headerOpcode = 2"));
			c->protocole._createIdentifiantPacket((int)c->getPlayer()->getId(), (int)_id);
			c->addOutput(c->protocole._getLastPacket());
			c->setState(PARAMETERS_SET);
		}
	}
	// ALL init
	else if (c->getState() == PARAMETERS_SET) {
		_log->addLog(std::string("[Game::HandleClientConnexion] : state = PARAMETERS_SET"));
		if (_proto._getHeaderOpcode() == 0) {
			std::cout << "INIT CLIENT" << std::endl;
			_log->addLog(std::string("[Game::HandleClientConnexion] : headerOpcode = 0"));
			_proto._setNewPacket(_initToClient[0]);
			std::cout << "Send [INIT CLIENT] : " <<  _proto._getArrayPositionLenght() << " sprites" << std::endl;
			for (size_t i = 0; _initToClient.size() > i; i++)
				c->addOutput(_initToClient[i]);
			c->setState(ID_SET);
		}
	}

	// Game OK, let's begin
	else if (c->getState() == ID_SET) {
		_log->addLog(std::string("[Game::HandleClientConnexion] : state = ID_SET"));
		if (_proto._getHeaderOpcode() == 0) {
			std::cout << " POSITION PACKET " << std::endl;
			_log->addLog(std::string("[Game::HandleClientConnexion] : headerOpcode = 0"));
			c->protocole._createResponsePacket(NONE);
			c->addOutput(c->protocole._getLastPacket());
			c->setState(POSITION_PACKET_SET);
			// faire spawn le joueur
			size_t x = ZONE + 5, y = 5, h = 0;
			c->getPlayer()->setY(y);
			c->getPlayer()->setX(x);
			while (checkCollisionAllObject(c->getPlayer()) && h < 500)
			{
				if (y < HEIGHT - c->getPlayer()->getHeight())
					c->getPlayer()->setY(y + 5);
				else
				{
					_log->addLog(std::string("Can't spawn player " + Tools::NumberToString(c->getPlayer()->getId())));
					throw std::runtime_error("Can't spawn player");
				}
				h++;
			}
			_log->addLog(std::string("[Game::HandleClientConnexion] Player spawn"));
			std::cout << "PLAYER SPAWN END -------------------------------------------------" << std::endl;
			int tmp = 0;
			// Send for the first time ALL the sprite position on the scene
			if (_objs != NULL)
			{
				for (size_t j = 0; j < _objs->size(); j++)
				{
					std::cout << RED << "Add OBJ" << WHITE << std::endl;
					std::string tmpType = "unknow";
					if ((*_objs)[j]->getType() == MISSILE)
					{
						Missile * m = reinterpret_cast<Missile *>((*_objs)[j]);
						tmpType = Tools::EMissileToString(m->getTypeMissile()).data();
					}
					if ((*_objs)[j]->getType() == UNKNOWN_OBJECT)
						std::cout << "Obj " << j << "is bad" << std::endl;
					_proto._addPositionPacket(
						(unsigned int)(*_objs)[j]->getX(),
						(unsigned int)(*_objs)[j]->getY(),
						(unsigned int)(*_objs)[j]->getWidth(),
						(unsigned int)(*_objs)[j]->getHeight(),
						(EObject)(*_objs)[j]->getType(),
						(Tools::getName((*_objs)[j]->getType(), (*_objs)[j]->getId()).c_str()),
						tmpType.data());
					tmp++;
				}
			}
			std::cout << "There are " << _clients.size() << " client(s)" << std::endl;
			for (size_t j = 0; j < _clients.size(); j++)
			{
				if (_clients[j]->getState() == POSITION_PACKET_SET) {
				std::cout << RED << "Add Player" << WHITE << std::endl;
					_proto._addPositionPacket(
						(unsigned int)_clients[j]->getPlayer()->getX(),
						(unsigned int)_clients[j]->getPlayer()->getY(),
						(unsigned int)_clients[j]->getPlayer()->getWidth(),
						(unsigned int)_clients[j]->getPlayer()->getHeight(),
						PLAYER,
						(Tools::getName(PLAYER, _clients[j]->getPlayer()->getId()).c_str()),
						"unknow");
					tmp++;
				}
			}
			if (tmp > 0)
			{
				_log->addLog(std::string("[Game::HandleClientConnexion] ERROR " + Tools::NumberToString(tmp) + " sprites"));
				_proto._putPositionPacketOnList();
				c->addOutput(_proto._getLastPacket());
				_proto._setNewPacket(_proto._getLastPacket());

			}
			std::cout << "[GAME :: HANDLE CONNEXION CLIENT ]There are : " << _proto._getArrayPositionLenght() << " sprites on packet " << std::endl;
			std::cout << std::string("[Game::HandleClientConnexion] Send " + Tools::NumberToString(tmp) + " sprites") << std::endl;
			_log->addLog(std::string("[Game::HandleClientConnexion] Send " + Tools::NumberToString(tmp) + " sprites"));
		}
	}
}

unsigned int Game::getIdThread() const
{
	return _idThread;
}

void Game::setIdThread(unsigned int i)
{
	_idThread = i;
}

bool Game::conditionCollision(AObject * one, AObject * two) const
{
	if (one->getId() == two->getId())
		return true;
	if (one->isDead() || two->isDead())
		return true;
	if ((one->getX() < two->getX() && two->getX() < one->getX() + one->getWidth())
		|| (one->getY() < two->getY() && two->getY() < one->getY() + one->getHeight()))
		return false;
	return true;
}

AObject* Game::listPlayer(AObject * obj) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		if (conditionCollision(obj, _clients[i]->getPlayer()) == false)
			return _clients[i]->getPlayer();
	return NULL;
}

AObject * Game::listObjects(AObject *obj) const
{
	if (_objs == NULL)
		return NULL;
	for (size_t i = 0; i < _objs->size(); i++)
		if (conditionCollision(obj, (*_objs)[i]) == false)
			return (*_objs)[i];
	return NULL;
}

AObject* Game::listMissiles(AObject * obj) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		for (size_t j = 0; i < _clients[i]->getPlayer()->missiles.size(); j++)
		if (conditionCollision(obj, _clients[i]->getPlayer()->missiles[j]) == false)
			return _clients[i]->getPlayer()->missiles[j];
	if (_objs != NULL)
	{
		for (size_t i = 0; i < _objs->size(); i++)
			if ((*_objs)[i]->getType() == MONSTER)
			{
				Monster * m = reinterpret_cast<Monster *>((*_objs)[i]);
				for (size_t j = 0; i < m->missiles.size(); j++)
					if (conditionCollision(obj, m->missiles[j]) == false)
						return m->missiles[j];
			}
	}
	return NULL;
}

void	Game::AllMove()
{
	for (size_t i = 0; i < _clients.size(); i++)
		for (size_t j = 0; i < _clients[i]->getPlayer()->missiles.size(); j++)
			_clients[i]->getPlayer()->missiles[j]->move(this, RIGHT, SPEED_MISSILE);
	if (_objs != NULL)
	{
		for (size_t i = 0; i < _objs->size(); i++)
		{
			(*_objs)[i]->move(this, LEFT, SPEED);
			if ((*_objs)[i]->getType() == MONSTER)
			{
				Monster * m = reinterpret_cast<Monster *>((*_objs)[i]);
				for (size_t j = 0; i < m->missiles.size(); j++)
					m->missiles[j]->move(this, LEFT, SPEED_MISSILE);
			}
		}
	}
}

bool	  Game::checkCollisionAllObject(AObject * entity) const
{
	if (checkCollisionObject("Player", entity))
		return false;
	if (checkCollisionObject("Objects", entity))
		return false;
	if (checkCollisionObject("Missile", entity))
		return false;
	return true;
}

AObject * Game::checkCollisionObject(const std::string & type, AObject* obj) const
{
	static bool check = true;
	static std::map<std::string, AObject* (Game::*)(AObject *)const> Tolist;

	if (check) {
		Tolist["Player"] = &Game::listPlayer;
		Tolist["Objects"] = &Game::listObjects;
		Tolist["Missile"] = &Game::listMissiles;
		check = false;
	}
	if (Tolist.count(type) > 0)
		return (this->*Tolist[type])(obj);
	_log->addLog("Collision with " + Tools::NumberToString(type) + " not implemented yet");
	return NULL;
}

bool			Game::isEnded(bool op) const
{
	bool result = false;
	if (op)
	  mutex->lock();
	if (_currwave == _waves.size())
		result = true;
	if (op)
	  mutex->unlock();
	return result;
}

bool			Game::nextWave()
{
	mutex->lock();
	_currwave++;
	if (isEnded(false))
		return true;
	_objs = _waves[_currwave];
	for (size_t i = 0; i < _waves[_currwave]->size(); i++)
	{
		AObject * tmp = (*_waves[_currwave])[i];
		//_objs->push_back(tmp);
		_proto._addPositionPacket((unsigned int)tmp->getX(),
			(unsigned int)tmp->getY(),
			(unsigned int)tmp->getWidth(),
			(unsigned int)tmp->getHeight(),
			tmp->getType(),
			(Tools::getName(tmp->getType(), tmp->getId())).c_str(), "unknown");
	}
	_proto._putPositionPacketOnList();
	_proto._setNewPacket(_proto._getLastPacket());
	if (_proto._getArrayPositionLenght() > 0)
		addPacketForClients(_proto._getLastPacket(), true);
	mutex->unlock();
	_log->addLog(std::string("[Game::nextWave] next waves " + Tools::NumberToString(_currwave)));
	return false;
}

bool			Game::isWaveEnded() const
{
	for (size_t i = 0; i < _waves[_currwave]->size(); i++)
		if (!(*_waves[_currwave])[i]->isDead())
			return false;
	return true;
}

void			Game::deleteWave()
{
	_objs = NULL;
	/*for (size_t i = 0; i < _waves[_currwave]->size(); i++)
	{
		size_t idToFind = (*_waves[_currwave])[i]->getId();
		for (size_t j = 0; i < _objs->size(); j++)
			if ((*_objs)[j]->getId() == idToFind)
			{
				_objs->erase(_objs->begin() + j);
			}
	}*/
}

void			Game::addPacketForClients(const char * packet, bool t)
{
	for (size_t i = 0; i < _clients.size(); i++)
		if (!t || (t && _clients[i]->getState() == POSITION_PACKET_SET))
			_clients[i]->addOutput(packet);
}

size_t			Game::getId() const
{
	return _id;
}

void			Game::monstersShoot()
{
	if (_objs != NULL)
	{
		for (size_t i = 0; i < _objs->size(); i++)
			if ((*_objs)[i]->getType() == MONSTER)
			{
				Monster * m = reinterpret_cast<Monster*>((*_objs)[i]);
				m->shoot(this);
			}
	}
}
