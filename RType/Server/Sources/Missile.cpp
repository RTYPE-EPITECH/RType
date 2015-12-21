#include "Missile.hpp"

Missile::Missile(void) : AObject()
{

}

Missile::~Missile()
{

}

// get / set
size_t Missile::getDamage()
{
	return _damage;
}
void Missile::setDamage(size_t d)
{
	_damage = d;
}

void Missile::setTypeMissile(EMissile e)
{
	_type = e;
}

EMissile Missile::getTypeMissile()
{
	return _type;
}

Missile * Missile::newInstance(EMissile t, size_t _x, size_t _y)
{
	Missile * m = new Missile();
	m->setTypeMissile(t);
	m->setX(_x);
	m->setY(_y);
	return m;
}