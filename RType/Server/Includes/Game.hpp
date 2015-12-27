#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include "IConditionVariable.hpp"
#include "Protocole.hpp"
#include "Log.hpp"

#define END				0
#define ZONE			100
#define SPAWN			500
#define WIDTH			800
#define HEIGHT			600
#define MAX_PLAYER_GAME	2
#define FPS				30
#define MAX_WAVES		2
#define SPEED			1
#define SPEED_PLAYER 	SPEED * 4
#define SPEED_OTHER		SPEED * 4
#define SPEED_MISSILE	SPEED * 8
#define SPEED_SHOT		SPEED * 0.5
#define SPEED_MOVE		SPEED * 0.001
#define SPEED_SHOT_ENEMY SPEED * 10
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
	Game(IConditionVariable *);
	~Game();
	bool init(const std::vector<std::string> &);
	bool addClient(Client *);
	void removeClient(Client *);
	bool loop();

	// get/set
	unsigned int getIdThread() const;
	void setIdThread(unsigned int);
	size_t getId() const;

	bool isEnded(bool op = true) const;
	size_t getSizeAvailable() const;

	void addPacketForClients(const char *, bool t = false);

	bool	  checkCollisionAllObject(AObject * entity) const;
	AObject * checkCollisionObject(const std::string & obj, AObject * entity) const;
	Protocole			_proto;

private:
	unsigned int _idThread;
	size_t _id;

	static std::vector<size_t> _ids;
	Log 					* _log;
	IConditionVariable * _condVar;
	IMutex				* mutex;
	ITimer				* timer;
	size_t				_currwave;
	size_t				_stateScroll;

	// Sprites present on the scene
	std::vector<Client *> _clients;
	std::vector<AObject *> * _objs;

	// All packet to send for client to be OK
	std::vector<const char *> _initToClient;

	// All the waves to launch
	std::vector< std::vector<AObject *> * > _waves;

	// checkInputAvailable
	bool haveInput(unsigned long long);

	// factorisation 
	bool handleInputClient(Client *);
	void handleClientConnexion(Client *);
	bool conditionCollision(AObject *, AObject *) const;

	AObject* listPlayer(AObject *) const;
	AObject * listObjects(AObject *) const;
	AObject* listMissiles(AObject *) const;

	void AllMove();
	void monstersShoot();
	void deleteWave();
	bool isWaveEnded() const;
	bool nextWave();
};

#endif /* GAME_HPP */
