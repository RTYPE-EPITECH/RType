#include "Game.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Obstacle.hpp"
#include "Client.hpp"
#include "Missile.hpp"
#include <iostream>

Game::Game(IConditionVariable & c) : _condVar(c)
{
	_currwave = 0;
	_stateScroll = 0;
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
	_clients.push_back(cl);
	cl->setState(CONNECT);
	// send id Game, id Player

	// send all init
	for (size_t i = 0; _initToClient.size() > i; i++)
		cl->addOutput(_initToClient[i]);
	return true;
}

int Game::getSizeAvailable() const
{
	return MAX_PLAYER_GAME - _clients.size();
}

bool Game::init(const std::vector<std::string> &)
{
	// Create waves and init monster with dynamic lib

	// init all the type of monster to the proto
	// store the command in special command to send



	return true;
}

bool Game::loop()
{
	while (1)
	{
		// For each client, get the oldest Input
		for (unsigned int i = 0; i < _clients.size(); i++)
		{
			char * input = NULL;
			if (!(input = _clients[i]->getInput()))
				break;
			// set input into protocole to have the get/set
			_proto._setNewPacket(input);
			handleInputClient(_clients[i]);
			// Move player or shoot 

			// Check Scene
		}

		// move the monster
	}
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
			m = c->getPlayer()->shoot();
			if (m != NULL)
			{
				c->getPlayer()->missiles.push_back(m);
				// send packet to create the missile
			}
		}
		else
		{
			if (c->getPlayer()->move(this, a, 1) == false)
			{
				// player dies
			}
			else
			{
				// send packet for the new position of player
			}
		}
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
	if (one->getX() < two->getX() && two->getX() < one->getX() + one->getWidth()
		|| one->getY() < two->getY() && two->getY() < one->getY() + one->getHeight())
		return false;
	return true;
}

bool Game::listPlayer(AObject * obj) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		if (conditionCollision(obj, _clients[i]->getPlayer()) == false)
			return true;
	return false;
}

bool Game::listMonster(AObject * obj) const
{
	for (size_t i = 0; i < _monsters->size(); i++)
		if (conditionCollision(obj, (*_monsters)[i]) == false)
			return true;
	return false;
}

bool Game::listObstacles(AObject * obj) const
{
	for (size_t i = 0; i < _obstacles.size(); i++)
		if (conditionCollision(obj, _obstacles[i]) == false)
			return true;
	return false;
}

bool Game::listMissiles(AObject * obj) const
{
	for (size_t i = 0; i < _clients.size(); i++)
		for (size_t j = 0; i < _clients[i]->getPlayer()->missiles.size(); j++)
		if (conditionCollision(obj, _clients[i]->getPlayer()->missiles[j]) == false)
			return true;
	return false;
}

bool Game::checkCollisionObject(const std::string & type, AObject* obj) const
{
	static bool check = true;
	static std::map<std::string, bool (Game::*)(AObject *)const> Tolist;

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
	return true;
}