#include "Client.hpp"
#include "ISocket.hpp"
#include "Game.hpp"
#include "IMutex.hpp"

Client::Client(IConditionVariable & con) : _condVar(con)
{
}

Client::~Client()
{
}

bool	Client::init()
{
	return true;
}

unsigned int Client::getIdThread() const
{
	return _idThread;
}

void Client::setIdThread(unsigned int i)
{
	_idThread = i;
}