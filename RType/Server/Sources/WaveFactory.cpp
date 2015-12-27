#include "WaveFactory.hpp"
#include "AObject.hpp"
#include "Obstacle.hpp"
#include "Monster.hpp"
#include "Game.hpp"
#include "MonsterFactory.hpp"

WaveFactory::WaveFactory()
{
	_waves = NULL;
}

WaveFactory::~WaveFactory()
{
}

void WaveFactory::addItem(AObject * obj, size_t x, size_t y, size_t with, size_t height)
{
	if (_waves == NULL)
		_waves = new std::vector<AObject *>;
	obj->setX(x);
	obj->setY(y);
	obj->setWidth(with);
	obj->setHeight(height);
	_waves->push_back(obj);
}

AObject * WaveFactory::getLastItem()
{
	if (_waves == NULL)
		return NULL;
	return _waves->back();
}

void WaveFactory::addItemNoPos(AObject * obj)
{
	AObject * prev = NULL;
	if ((prev = getLastItem()) != NULL)
		addItem(obj, SPAWN,
			prev->getY() + prev->getHeight() + 50,
			obj->getWidth(), obj->getHeight());
	else
		addItem(obj, SPAWN, 50, obj->getWidth(), obj->getHeight());
}

void WaveFactory::addObstacle()
{
	addItemNoPos(new Obstacle());
}

void WaveFactory::addMonster(const std::string & type)
{
	MonsterFactory *m = MonsterFactory::getInstance();
	addItemNoPos(m->getInstanceMonster(type));
}

void WaveFactory::addMonster()
{
	MonsterFactory *m = MonsterFactory::getInstance();
	addItemNoPos(m->getInstanceMonster());
}

std::vector<AObject *> * WaveFactory::getWaves()
{
	std::vector<AObject *> * tmp = _waves;
	_waves = NULL;
	return tmp;
}
