#include "Client.hpp"
#include "ISocket.hpp"
#include "Game.hpp"
#include "IMutex.hpp"
#include "Player.hpp"

#ifndef _WIN32
# include "USocket.hpp"
# include "UMutex.hpp"
#else
# include "WSocket.hpp"
# include "WMutex.hpp"
#endif

Client::Client()
{
#ifndef _WIN32
	_mutexOutput = new UMutex();
	_mutexInput = new UMutex();
#else
	_mutexOutput = new WMutex();
	_mutexInput = new WMutex();
#endif
	_socket = NULL;
	/*ip = _ip;
	port = _port;*/
	player = NULL;
	_game = NULL;
	_state = DISCONNECT;
}

Client::~Client()
{
}

bool	Client::init(Game * g)
{
	if (!_mutexInput->initialize() || !_mutexOutput->initialize())
		return false;
	player = new Player();
	_game = g;
	return true;
}

size_t	Client::getIdThreadGame()
{
	if (_game)
		return _game->getIdThread();
	throw std::runtime_error("[Client] No game instancied");
	return 0;
}

char *	Client::getInput()
{
	char * result = NULL;
	_mutexInput->lock();
	if (_input.size() > 0)
	{
		result = _input[0];
		_input.erase(_input.begin());
	}
	_mutexInput->unlock();
	return result;
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

void	Client::addOutput(char * e)
{
	_mutexInput->lock();
	_output.push_back(e);
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

STATE_CONNECT Client::getState() const
{
	return _state;
}

void Client::setState(STATE_CONNECT e)
{
	_state = e;
}

void			Client::setSocket(ISocket *s)
{
	_socket = s;
}

ISocket * Client::getSocket() const
{
	return _socket;
}