#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <string>
#include "IConditionVariable.hpp"
#include "Protocole.hpp"

class ISocket;
class Game;
class IMutex;

class Client
{
public:
	Client(IConditionVariable &);
	~Client();
	bool init();

	// get/set
	unsigned int getIdThread() const;
	void setIdThread(unsigned int);

private:
	ISocket * _socket;
	std::string ip;
	int port;
	unsigned int _idThread;
	Game  * _game;
	IMutex * _mutex;
	IConditionVariable & _condVar;
	std::vector<char *> _input;
	std::vector<char *> _output;
	Protocole _proto;
};

#endif /* CLIENT_HPP */