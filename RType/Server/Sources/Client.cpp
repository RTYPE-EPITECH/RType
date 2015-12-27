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
	player = NULL;
	_game = NULL;
	isUDPset = false;
	_state = BEGINNING;
	isUDPset = false;
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

const char *	Client::getInput()
{
	const char * result = NULL;
	_mutexInput->lock();
	if (_input.size() > 0)
	{
		result = _input[0];
		_input.erase(_input.begin());
	}
	_mutexInput->unlock();
	return result;
}

const char *	Client::getOutput()
{
	const char * result = NULL;
	_mutexOutput->lock();
	if (_output.size() > 0)
	{
		result = _output[0];
		_output.erase(_output.begin());
	}
	_mutexOutput->unlock();
	return result;
}

std::vector<const char *> Client::getAllOutput()
{
	std::vector<const char *> _res;
	_mutexOutput->lock();
	if (_output.size() > 0)
	{
		_res = _output;
		_output.clear();
	}
	_mutexOutput->unlock();
	return _res;
}

std::vector<const char *> Client::getAllInput()
{
	std::vector<const char *> _res;
	_mutexInput->lock();
	if (_input.size() > 0)
	{
		_res = _input;
		_input.clear();
	}
	_mutexInput->unlock();
	return _res;
}

bool			Client::haveInput()
{
	bool tmp = false;
	_mutexInput->lock();
	if (_input.size() > 0)
		tmp = true;
	_mutexInput->unlock();
	return tmp;
}

bool			Client::haveOutput()
{
	bool tmp = false;
	_mutexOutput->lock();
	if (_output.size() > 0)
		tmp = true;
	_mutexOutput->unlock();
	return tmp;
}

void	Client::addInput(const char * e)
{
	_mutexInput->lock();
	_input.push_back(e);
	_mutexInput->unlock();
}

void	Client::addOutput(const char * e)
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

ESTATE Client::getState() const
{
	_mutexInput->lock();
ESTATE tmp = _state;
	_mutexInput->unlock();
return tmp;
}

void Client::setState(ESTATE e)
{
_mutexInput->lock();
	_state = e;
_mutexInput->unlock();

}

void			Client::setSocket(ISocket *s)
{
	_socket = s;
}

ISocket * Client::getSocket() const
{
	return _socket;
}
