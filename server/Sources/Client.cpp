#include "Client.hpp"
#include "ISocket.hpp"
#include "Game.hpp"
#include "IMutex.hpp"

#ifndef WIN_32
# include "USocket.hpp"
# include "UMutex.hpp"
#else
# include "WSocket.hpp"
# include "WMutex.hpp"
#endif

Client::Client(Game * g, const std::string & _ip, short _port) : _game(g)
{
#ifndef WIN_32
	_socket = new USocket(0);
	_mutexOutput = new UMutex();
	_mutexInput = new UMutex();
#else
	_socket = new WSocket(0);
	_mutexOutput = new WMutex();
	_mutexInput = new WMutex();
#endif
	ip = _ip;
	port = _port;
	player = NULL;
	_state = DISCONNECT;
}

Client::~Client()
{
}

bool	Client::init()
{
	if (!_mutexInput->initialize() || !_mutexOutput->initialize())
		return false;
	return true;
}

bool	Client::getOldestInput()
{
	_mutexInput->lock();
	// Charge Input in Protocole
	_mutexInput->unlock();
	return true;
}

char *	Client::getOutput()
{
	char * result = NULL;
	_mutexOutput->lock();
	if (_output.size() > 0)
	{
		result = _output[0];
		_output.erase(_output.begin());
	}
	_mutexOutput->unlock();
	return result;
}

void	Client::addInput(char * e)
{
	_mutexInput->lock();
	_input.push_back(e);
	_mutexInput->unlock();
}

Player * Client::getPlayer() const
{
	return player;
}

void	Client::setPlayer(Player *p)
{
	player = p;
}
