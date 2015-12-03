#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "IConditionVariable.hpp"
#include "Protocole.hpp"

class Client;
class Player;
class Monster;
class Obstacle;

class Game
{
public:
	Game(IConditionVariable &);
	~Game();
	bool init();
	bool loop();

	// get/set
	unsigned int getIdThread() const;
	void setIdThread(unsigned int);

private:
	unsigned int _idThread;
	IConditionVariable & _condVar;
	Protocole			_proto;
	std::vector<Client *> _clients;
	std::vector<Monster*> _monsters;
	std::vector<Obstacle *> _obstacles;
};

#endif /* GAME_HPP */