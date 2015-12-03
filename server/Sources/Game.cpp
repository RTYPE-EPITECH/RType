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
	// For each client, get the oldest Input
	for (unsigned int i = 0; i < _clients.size(); i++)
	{
		char * input = NULL;
		if (!(input = _clients[i]->getInput()))
			break;
		// set input into protocole to have the get/set

		// Move player or shoot 
		// Check Scene

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