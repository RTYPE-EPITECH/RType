#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "AObject.hpp"
#include "EMissile.hpp"

class Missile;

class Player : public AObject {
public:
	Player(Protocole &);
	~Player();

	Missile * shoot();

	// get / set
	size_t getLife() const;
	size_t getMaxLife() const;
	size_t getMaxMissile() const;
	EMissile getTypeMissile() const;

	void setLife(size_t);
	void setMaxLife(size_t);
	void setMaxMissile(size_t);
	void setTypeMissile(EMissile);

	std::vector<Missile *> missiles;
private:
	size_t life;
	size_t maxLife;
	size_t maxMissile;
	EMissile typeMissile;
};

#endif /* PLAYER_HPP */