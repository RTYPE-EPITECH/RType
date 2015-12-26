#include "Monster.hpp"
#include "Missile.hpp"
#ifdef _WIN32
#include "WTimer.hpp"
#else
#include "UTimer.hpp"
#endif
#include "Game.hpp"
#include "Tools.hpp"

Monster::Monster(void) : AObject()
{
	life = 1;
	maxLife = 1;
	monsterType = "normalMonster";
#ifdef _WIN32
	_t = new WTimer();
#else
	_t = new UTimer();
#endif
	_t->start();
	type = MONSTER;
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

Missile * Monster::shoot(Game *g)
{
	if (_t->getElapsedTimeInMicroSec() > SPEED_SHOT_ENEMY * 1000000)
	{
		currentMissile++;
		missiles.push_back(Missile::newInstance(typeMissile, x + width + 1, y + width / 2));
		_proto._addPositionPacket(
			(unsigned int)missiles.back()->getX(),
			(unsigned int)missiles.back()->getY(),
			(unsigned int)missiles.back()->getWidth(),
			(unsigned int)missiles.back()->getHeight(),
			(EObject)missiles.back()->getType(),
			(Tools::getName(missiles.back()->getType(), missiles.back()->getId()).c_str()),
			Tools::EMissileToString(typeMissile).data());
		_proto._putPositionPacketOnList();
		g->addPacketForClients(_proto._getLastPacket(), true);
		_t->start();
		return missiles.back();
	}
	return NULL;
}

std::string Monster::getTypeMonster() const
{
	return monsterType;
}

void	Monster::loadIMonster(IMonster * m)
{
	life = m->getLife();
	maxLife = m->getMaxLife();
	maxMissile = m->getMaxMissile();
	typeMissile = m->getTypeMissile();
	monsterType = m->getTypeMonster();
}
