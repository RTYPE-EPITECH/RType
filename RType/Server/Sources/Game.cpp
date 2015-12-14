#include "Game.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Obstacle.hpp"
#include "Client.hpp"
#include "Missile.hpp"
#include <iostream>

#ifdef WIN32
# include "WTimer.hpp"
# include "WMutex.hpp"
#else
# include "UTimer.hpp"
# include "UMutex.hpp"
#endif

Game::Game(IConditionVariable & c) : _condVar(c)
{
	_currwave = 0;
	_stateScroll = 0;
	timer = NULL;
	_idThread = 0;
}

Game::~Game()
{
}

bool Game::addClient(Client * cl)
{
	if (getSizeAvailable() <= 0)
		return false;
	if (cl->init(this))
		return false;
	mutex->lock();
	_clients.push_back(cl);
	mutex->unlock();
	cl->setState(CONNECT);
	// send id Game, id Player

	// send all init
	for (size_t i = 0; _initToClient.size() > i; i++)
		cl->addOutput(_initToClient[i]);
	return true;
}

int Game::getSizeAvailable() const
{
	mutex->lock();
	int size = MAX_PLAYER_GAME - _clients.size();
	mutex->unlock();
	return size;
}

bool Game::init(const std::vector<std::string> &)
{
	// Create waves and init monster with dynamic lib

	// init all the type of monster to the proto
	// store the command in special command to send


#ifdef WIN32
	timer = new WTimer();
	mutex = new WMutex();
#else
	timer = new UTimer();
	mutex = new UMutex();
#endif
	if (!mutex->initialize())
		return false;
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
		_condVar.wait(t);
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
  while (1)
    {
      if (haveInput(FPS * 1000 - timer->getElapsedTimeInMicroSec()))
	{
	  mutex->lock();
	  // For each client, get the oldest Input
	  for (size_t i = 0; i < _clients.size(); i++)
	    {
	      char * input = NULL;
	      if (!(input = _clients[i]->getInput()))
		continue;
	      // set input into protocole to have the get/set
	      _proto._setNewPacket(input);
	      handleInputClient(_clients[i]);
	    }
	  //_proto._putPositionPacketOnList();
	  //_proto._getLastPacket();
	  mutex->unlock();
	}
      // Check Scene :: Move Missile, Move scroll, Move enemies, Move Obstacles
      if (timer->getElapsedTimeInMicroSec() == FPS * 1000)
	{
	  mutex->lock();
	  AllMove();
	  mutex->unlock();
	  timer->start();
	}
      //packet scroll
    }
  return true;
}

bool	Game::handleObjestScene()
{
	// Missiles

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
      // send Packet error
      std::cerr << "NEED SEND PACKET ERROR - CHECK THE CODE" << std::endl;
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

AObject* Game::listMonster(AObject * obj) const
{
	for (size_t i = 0; i < _monsters->size(); i++)
		if (conditionCollision(obj, (*_monsters)[i]) == false)
			return (*_monsters)[i];
	return NULL;
}

AObject* Game::listObstacles(AObject * obj) const
{
	for (size_t i = 0; i < _obstacles.size(); i++)
		if (conditionCollision(obj, _obstacles[i]) == false)
			return _obstacles[i];
	return NULL;
}

AObject* Game::listMissiles(AObject * obj) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		for (size_t j = 0; i < _clients[i]->getPlayer()->missiles.size(); j++)
		if (conditionCollision(obj, _clients[i]->getPlayer()->missiles[j]) == false)
			return _clients[i]->getPlayer()->missiles[j];
	for (size_t i = 0; i < _monsters->size(); i++)
		for (size_t j = 0; i < (*_monsters)[i]->missiles.size(); j++)
			if (conditionCollision(obj, (*_monsters)[i]->missiles[j]) == false)
				return (*_monsters)[i]->missiles[j];
	return NULL;
}

void	Game::AllMove()
{
	for (size_t i = 0; i < _clients.size(); i++)
		for (size_t j = 0; i < _clients[i]->getPlayer()->missiles.size(); j++)
		{
			_clients[i]->getPlayer()->missiles[j]->move(this, RIGHT, 4);
			//Create packet Move Sprite
		}
	for (size_t i = 0; i < _monsters->size(); i++)
	{
		(*_monsters)[i]->move(this, LEFT, 1);
		// packet move sprite
		for (size_t j = 0; i < (*_monsters)[i]->missiles.size(); j++)
		{
			(*_monsters)[i]->missiles[j]->move(this, LEFT, 4);
			//create packet Move Sprite
		}
	}
	for (size_t i = 0; i < _obstacles.size(); i++)
	{
		_obstacles[i]->move(this, LEFT, 1);
		//create packet move
	}
}

AObject * Game::checkCollisionObject(const std::string & type, AObject* obj) const
{
	static bool check = true;
	static std::map<std::string, AObject* (Game::*)(AObject *)const> Tolist;

	if (check) {
		Tolist["Player"] = &Game::listPlayer;
		Tolist["Monster"] = &Game::listMonster;
		Tolist["Obstacle"] = &Game::listObstacles;
		Tolist["Missile"] = &Game::listObstacles;
		check = false;
	}
	if (Tolist.count(type) > 0)
		return (this->*Tolist[type])(obj);
	std::cerr << "Collision with " << type << " not implemented yet" << std::endl;
	return NULL;
}
