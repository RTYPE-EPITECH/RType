#include "AObject.hpp"
#include "Game.hpp"
#include <map>
#include <iostream>
#include "Missile.hpp"
#include "Player.hpp"
#include "Monster.hpp"

std::vector<size_t> AObject::_ids;

AObject::AObject(Protocole & _p) : _proto(_p)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	type = UNKNOWN_OBJECT;
	_dead = false;
	id = _ids.size();
	_ids.push_back(id);
}

AObject::AObject(const AObject & other) : _proto(other._proto)
{
	x = other.x;
	y = other.y;
	width = other.width;
	height = other.height;
	type = other.type;
	_dead = other._dead;
}

AObject & AObject::operator=(const AObject & other)
{
	x = other.x;
	y = other.y;
	width = other.width;
	height = other.height;
	type = other.type;
	_dead = other._dead;
	return (*this);
}

AObject::~AObject()
{
}

size_t	AObject::getId() const
{
	return id;
}

size_t	AObject::getX() const
{
	return x;
}
size_t	AObject::getY() const
{
	return y;
}
size_t	AObject::getWidth() const
{
	return width;
}
size_t	AObject::getHeight() const
{
	return height;
}
EObject	AObject::getType() const
{
	return type;
}

bool AObject::isDead() const
{
	return _dead;
}

void	AObject::setX(size_t _x)
{
	x = _x;
}

void	AObject::setY(size_t _y)
{
	y = _y;
}

void	AObject::setWidth(size_t _w)
{
	width = _w;
}

void	AObject::setHeight(size_t _h)
{
	height = _h;
}

void	AObject::setType(EObject _t)
{
	type = _t;
}

void	AObject::moveRight(size_t &x , size_t &, size_t s) const
{
	x += s;
}

void	AObject::moveLeft(size_t &x, size_t &, size_t s) const
{
	x -= s;
}

void	AObject::moveTop(size_t &, size_t &y, size_t s) const
{
	y -= s;
}
void	AObject::moveBot(size_t &, size_t &y, size_t s) const
{
	y += s;
}

bool	AObject::move(Game * g, ACTION a, size_t t)
{
	static std::map<ACTION,
					void(AObject::*)(size_t &, 
									size_t &, 
									size_t) const> tomove;
	static bool check = true;
	size_t fx = x;
	size_t fy = y;
	if (check == true) {
		tomove[UP] = &AObject::moveTop;
		tomove[DOWN] = &AObject::moveBot;
		tomove[LEFT] = &AObject::moveLeft;
		tomove[RIGHT] = &AObject::moveRight;
		check = false;
	}
	(this->*tomove[a])(fx, fy, t);

	// Check collision with Player/ScreenEdge. If true, then do nothing
	if (g->checkCollisionObject("Player", this) != NULL
		|| g->checkCollisionObject("Screen", this) != NULL)
		return true;

	// check collision with enemies/obstacle/missile . If true, then player dies
	if (g->checkCollisionObject("Monster", this) != NULL
		|| g->checkCollisionObject("Obstacle", this) != NULL)
	{
		die(g);
		return false;
	}
	// Collision with Missile : Takin Dmg
	AObject * o = g->checkCollisionObject("Missile", this);
	if (o != NULL)
	{
		Missile * m = reinterpret_cast<Missile *>(o);
		//descrease life
		if (type == PLAYER)
		{
			Player * p = reinterpret_cast<Player *>(this);
			p->setLife(p->getLife() - m->getDamage());
			if (p->getLife() == 0)
				die(g);
		}
		else if (type == MONSTER)
		{
			Monster * p = reinterpret_cast<Monster *>(this);
			p->setLife(p->getLife() - m->getDamage());
			if (p->getLife() == 0)
				die(g);
		}
		o->die(g);
	}
	if (isDead())
		return false;
	// no collision, apply position
	x = fx;
	y = fy;
	// Create PACKET to move
	return true;
}

void	AObject::die(Game *)
{
	// create Packet die
	_dead = true;
}