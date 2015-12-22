#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <string>
#include "Protocole.hpp"
#include "StateConnexion.hpp"
#include "ISocket.hpp"

class Game;
class IMutex;
class Player;

class Client
{
public:
	Client();
	~Client();
	bool init(Game *);

	// get/set player object
	Player * getPlayer() const;
	void	setPlayer(Player *);

	ESTATE getState() const;
	void setState(ESTATE);

	void	setSocket(ISocket *);
	ISocket *	getSocket() const;

	size_t	getIdThreadGame();

	// Mutexed function to get input/output from vector
	const char *	getInput();
	const char *	getOutput();

	std::vector<const char *> getAllOutput();

	// Mutexed function to add input/output to vector
	void	addInput(const char *);
	void	addOutput(const char *);

	Protocole protocole;
	ISocket::tSocketAdress _adr;
private:
	ISocket * _socket;

	std::string ip;
	short port;

	ESTATE _state;
	Game  * _game;
	Player * player;

	IMutex * _mutexOutput;
	IMutex * _mutexInput;
	std::vector<const char *> _input;
	std::vector<const char *> _output;

};

#endif /* CLIENT_HPP */