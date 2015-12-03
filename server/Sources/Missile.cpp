#include "Missile.hpp"

Missile::Missile(Protocole &p) : AObject(p)
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

void Missile::setType(EMissile e)
{
	_type = e;
}

EMissile Missile::getType()
{
	return _type;
}

Missile * Missile::newInstance(Protocole & e, EMissile t, size_t x, size_t y)
{
	Missile * m = new Missile(e);
	m->setType(t);
	return m;
}