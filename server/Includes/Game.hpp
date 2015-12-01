#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

class Player;
class Monster;
class Obstacle;

class Game
{
public:
	Game();
	~Game();
	bool init();
	bool loop();
private:
	Player * player;
	std::vector<Monster*> _monsters;
	std::vector<Obstacle *> _obstacles;
};

#endif /* GAME_HPP */