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
}

Game::~Game()
{
	if (timer)
		delete(timer);
	if (mutex)
		delete(mutex);
	if (_objs)
		delete(_objs);
}

bool Game::addClient(Client * cl)
{
	if (getSizeAvailable() <= 0)
		return false;
	std::cout << "Enough place" << std::endl;
	if (!cl->init(this))
		return false;
	std::cout << "Client init" << std::endl;
	mutex->lock();
	_clients.push_back(cl);
	mutex->unlock();
	cl->setState(CONNECT);
	// send id Game, id Player
	cl->protocole._createParametersPacket((int)_id, (int)cl->getPlayer()->getId());
	cl->addOutput(cl->protocole._getLastPacket());
	// send all init
	for (size_t i = 0; _initToClient.size() > i; i++)
		cl->addOutput(_initToClient[i]);
	return true;
}

void Game::removeClient(Client * c)
{
	mutex->lock();
	for (std::vector<Client *>::iterator i = _clients.begin(); 
			i != _clients.end(); ++i)
		if ((*i)->getPlayer()->getId() == c->getPlayer()->getId())
			_clients.erase(i);
	mutex->unlock();
}

size_t Game::getSizeAvailable() const
{
	mutex->lock();
	size_t size = MAX_PLAYER_GAME - _clients.size();
	mutex->unlock();
	return size;
}

bool Game::init(const std::vector<std::string> & _lib)
{
	// init Monsters Library AND create Init packet Cmd
	MonsterFactory * mf = MonsterFactory::getInstance();
	for (size_t i = 0; i < _lib.size(); i++)
		mf->addLibrary(_lib[i]);
	std::vector<std::string> _monsters = mf->getAllMonsterName();
	for (size_t i = 0; i < _monsters.size(); i++)
		_proto._addPositionPacket(0, 0, 0, 0, MONSTER, _monsters[i].c_str(), _monsters[i].c_str());
	_proto._addPositionPacket(0, 0, 0, 0, PLAYER, "Player", "Player");
	_proto._addPositionPacket(0, 0, 0, 0, MISSILE, "Missile", "Missile");
	_proto._addPositionPacket(0, 0, 0, 0, OBSTACLE, "Obstacle", "Obstacle");
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
	std::cout << "Game " << _id << " initialized : " << _waves.size() << " waves " << std::endl;
	return true;
}

bool Game::haveInput(unsigned long long t)
{
	bool check = false;
	char * input = NULL;
	mutex->lock();
	for (unsigned int i = 0; i < _clients.size(); i++)
		if ((input = _clients[i]->getInput()))
		{
			check = true;
			break;
		}
	mutex->unlock();
	if (!check)
		_condVar->wait(t);
	mutex->lock();
	for (unsigned int i = 0; i < _clients.size(); i++)
		if ((input = _clients[i]->getInput()))
		{
			check = true;
			break;
		}
	mutex->unlock();
	return check;
}

bool Game::loop()
{
	timer->start();
  while (!isEnded())
    {
		if (_clients.size() == 0)
		{
			std::cout << "0 client, so we wait" << std::endl;
			_condVar->wait();
		}
		std::cout << FPS * 1000 << " - " << timer->getElapsedTimeInMicroSec() << std::endl;
		if (haveInput(FPS * 1000 - timer->getElapsedTimeInMicroSec()))
		{
		  mutex->lock();
		  // For each client, get the oldest Input
		  for (size_t i = 0; i < _clients.size(); i++)
				if (GAME_CREATED == _clients[i]->getState())
				{
					char * input = NULL;
					if (!(input = _clients[i]->getInput()))
						continue;
					// set input into protocole to have the get/set
					_proto._setNewPacket(input);
					handleInputClient(_clients[i]);
				}
		  _proto._putPositionPacketOnList();
		  addPacketForClients(_proto._getLastPacket());
		  mutex->unlock();
		}

		// Check Scene :: Move Missile, Move scroll, Move enemies, Move Obstacles
		if (timer->getElapsedTimeInMicroSec() == FPS * 1000)
		{
			std::cout << "Game " << _id << "Let's scroll da game" << std::endl;
		  mutex->lock();
		  AllMove();
		  _proto._putPositionPacketOnList();
		  addPacketForClients(_proto._getLastPacket());
		  mutex->unlock();
		  timer->start();
		}
		monstersShoot();
		if (isWaveEnded())
		{
			std::cout << "Game " << _id << " wave ended... NEXT" << std::endl;
			deleteWave();
			nextWave();
		}
    }
  // PACKET GAME FINIE
  std::cout << "Game " << _id << " finished" << std::endl;
  return true;
}

bool	Game::handleInputClient(Client * c)
{
  if (_proto._getHeaderOpcode() != 3)
    {
      ACTION a = (ACTION)_proto._getActionOpcode();
      Missile * m = NULL;
      if (a == SHOOT)
	{
	  if ((m = c->getPlayer()->shoot(this)) == NULL)
	    std::cout << "Player " << c->getPlayer()->getId() << " cannot shoot" << std::endl;
	}
      else
	if (c->getPlayer()->move(this, a, 1) == false)
	  std::cout << "Player " << c->getPlayer()->getId() << " die" << std::endl;
    }
  else
    {
		_proto._createResponsePacket(INVALID_ACTION);
		c->addOutput(_proto._getLastPacket());
    }
  return true;
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
	std::cerr << "Collision with " << type << " not implemented yet" << std::endl;
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
	addPacketForClients(_proto._getLastPacket());
	mutex->unlock();
	std::cout << "Game " << _id << " next waves " << _currwave << std::endl;
	return false;
}

bool			Game::isWaveEnded() const
{
	for (size_t i = 0; i < _waves[_currwave]->size(); i++)
		if (!(*_waves[_currwave])[i]->isDead())
			return false;
	mutex->lock();
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

void			Game::addPacketForClients(char * packet)
{
	for (size_t i = 0; i < _clients.size(); i++)
		_clients[i]->addOutput(packet);
}

size_t			Game::getId() const
{
	return _id;
}

void			Game::monstersShoot()
{
if (_objs != NULL)
	for (size_t i = 0; i < _objs->size(); i++)
		if ((*_objs)[i]->getType() == MONSTER)
		{
			Monster * m = reinterpret_cast<Monster*>((*_objs)[i]);
			m->shoot(this);
		}
}
