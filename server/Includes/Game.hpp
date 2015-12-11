#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include "IConditionVariable.hpp"
#include "Protocole.hpp"

#define END				0
#define ZONE			100
#define SPAWN			500
#define MAX_PLAYER_GAME	4

class AObject;
class Client;
class Player;
class Monster;
class Obstacle;

class Game
{
public:
	Game(IConditionVariable &);
	~Game();
	bool init(const std::vector<std::string> &);
	bool addClient(Client *);
	bool loop();

	// get/set
	unsigned int getIdThread() const;
	void setIdThread(unsigned int);

	int	getSizeAvailable() const;

	bool checkCollisionObject(const std::string &, AObject *) const;

private:
	unsigned int _idThread;
	IConditionVariable & _condVar;
	Protocole			_proto;

	// Sprites present on the scene
	std::vector<Client *> _clients;
	std::vector<Monster*> * _monsters;
	std::vector<Obstacle *> _obstacles;

	// All packet to send for client to be OK
	std::vector<char *> _initToClient;

	// All the waves to launch
	std::map<size_t, std::vector<Monster *> * > _waves;
	size_t					_currwave;
	size_t					_stateScroll;

	bool handleInputClient(Client *);
	bool conditionCollision(AObject *, AObject *) const;

	bool listPlayer(AObject *) const;
	bool listMonster(AObject *) const;
	bool listObstacles(AObject *) const;
	bool listMissiles(AObject *) const;
};

#endif /* GAME_HPP */