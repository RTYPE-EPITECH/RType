#include "Game.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Obstacle.hpp"
#include "Client.hpp"

Game::Game(IConditionVariable & c) : _condVar(c)
{
}

Game::~Game()
{
}

bool Game::init()
{
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
			m = c->getPlayer()->shoot();
		else
			c->getPlayer()->move(a, 1);
	}
	else
	{
		// send Packet error
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