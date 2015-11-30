#include "Client.hpp"
#include "ISocket.hpp"
#include "Game.hpp"
#include "IMutex.hpp"

Client::Client(Game * g) : _game(g)
{
}

Client::~Client()
{
}

bool	Client::init()
{
	return true;
}

Player * Client::getPlayer() const
{
	return player;
}

void	Client::setPlayer(Player *p)
{
	player = p;
}