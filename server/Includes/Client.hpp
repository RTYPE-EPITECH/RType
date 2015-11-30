#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <string>
#include "Protocole.hpp"

class ISocket;
class Game;
class IMutex;
class Player;

class Client
{
public:
	Client(Game * g);
	~Client();
	bool init();

	// get/set
	Player * getPlayer() const;
	void	setPlayer(Player *);

private:
	ISocket * _socket;
	std::string ip;
	int port;
	Game  * _game;
	IMutex * _mutex;
	Player * player;
	std::vector<char *> _input;
	std::vector<char *> _output;
	Protocole _proto;
};

#endif /* CLIENT_HPP */