#include "Player.hpp"
#include "Missile.hpp"

Player::Player(void) : AObject()
{
	life = 10;
	maxLife = 10;
	maxMissile = 3;
	currentMissile = 0;
	typeMissile = NORMAL;
}

Player::~Player() {}

Missile * Player::shoot(Game *)
{
	if (currentMissile < maxMissile)
	{
		currentMissile++;
		missiles.push_back(Missile::newInstance(typeMissile, x + width + 1, y + width / 2));
		// CREATE PACKET NEW SPRITE
		return missiles.back();
	}
	return NULL;
}

size_t Player::getLife() const
{
	return life;
}

size_t Player::getMaxLife() const
{
	return maxLife;
}

size_t Player::getMaxMissile() const
{
	return maxMissile;
}

EMissile Player::getTypeMissile() const
{
	return typeMissile;
}

void Player::setLife(size_t l)
{
	life = l;
}

void Player::setMaxLife(size_t l)
{
	maxLife = l;
}

void Player::setMaxMissile(size_t l)
{
	maxMissile = l;
}

void Player::setTypeMissile(EMissile t)
{
	typeMissile = t;
}