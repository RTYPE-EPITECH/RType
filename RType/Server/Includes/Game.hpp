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
#define FPS				30

class AObject;
class Client;
class Player;
class Monster;
class Obstacle;
class ITimer;
class IMutex;

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

	AObject * checkCollisionObject(const std::string & obj, AObject * entity) const;
  Protocole			_proto;
private:
	unsigned int _idThread;
	IConditionVariable & _condVar;
	IMutex				* mutex;
	ITimer				* timer;
	size_t				_currwave;
	size_t				_stateScroll;

	// Sprites present on the scene
	std::vector<Client *> _clients;
	std::vector<Monster*> * _monsters;
	std::vector<Obstacle *> _obstacles;

	// All packet to send for client to be OK
	std::vector<char *> _initToClient;

	// All the waves to launch
	std::map<size_t, std::vector<Monster *> * > _waves;

	// checkInputAvailable
	bool haveInput(unsigned long long);

	// factorisation 
	bool handleInputClient(Client *);
	bool handleObjestScene();
	bool conditionCollision(AObject *, AObject *) const;

	AObject* listPlayer(AObject *) const;
	AObject* listMonster(AObject *) const;
	AObject* listObstacles(AObject *) const;
	AObject* listMissiles(AObject *) const;

	void AllMove();
};

#endif /* GAME_HPP */
