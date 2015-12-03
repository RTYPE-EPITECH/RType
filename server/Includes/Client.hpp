#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <string>
#include "Protocole.hpp"
#include "StateConnexion.hpp"

class ISocket;
class Game;
class IMutex;
class Player;

class Client
{
public:
	Client(Game * g, const std::string &, short);
	~Client();
	bool init();

	// get/set player object
	Player * getPlayer() const;
	void	setPlayer(Player *);

	// Mutexed function to get input/output from vector
	char *	getInput();
	char *	getOutput();

	// Mutexed function to add input/output to vector
	void	addInput(char *);
	void	addOutput(char *);

private:
	ISocket * _socket;

	std::string ip;
	short port;

	STATE_CONNECT _state;
	Game  * _game;
	Player * player;

	IMutex * _mutexOutput;
	IMutex * _mutexInput;
	std::vector<char *> _input;
	std::vector<char *> _output;

};

#endif /* CLIENT_HPP */