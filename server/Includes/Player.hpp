#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "AObject.hpp"

class Player : public AObject {
	Player(Protocole &);
	~Player();

private:
	size_t life;
	size_t maxLife;
	size_t maxMissible;
	EMissile typeMissile;
	std::vector<Missile *> missiles;
};

#endif /* PLAYER_HPP */