#include "Monster.hpp"
#include "Missile.hpp"

Monster::Monster(void) : AObject()
{
	life = 1;
	maxLife = 1;
}

Monster::~Monster()
{
}

size_t Monster::getLife() const
{
	return life;
}

size_t Monster::getMaxLife() const
{
	return maxLife;
}

void Monster::setLife(size_t l)
{
	life = l;
}

void Monster::setMaxLife(size_t l)
{
	maxLife = l;
}

void Monster::setMaxMissile(size_t l)
{
	maxMissile = l;
}

void Monster::setTypeMissile(EMissile t)
{
	typeMissile = t;
}

size_t Monster::getMaxMissile() const
{
	return maxMissile;
}

EMissile Monster::getTypeMissile() const
{
	return typeMissile;
}

Missile * Monster::shoot(Game *)
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