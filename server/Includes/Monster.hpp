#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "AObject.hpp"
#include "EMissile.hpp"

class Monster : public AObject
{
public:
	Monster(Protocole &);
	~Monster();

	size_t getLife() const;
	size_t getMaxLife() const;
	size_t getMaxMissile() const;
	EMissile getTypeMissile() const;

	void setLife(size_t);
	void setMaxLife(size_t);
	void setMaxMissile(size_t);
	void setTypeMissile(EMissile);

protected:
	size_t life;
	size_t maxLife;
	size_t maxMissile;
	size_t currentMissile;
	EMissile typeMissile;
};
#endif /* MONSTER_HPP */