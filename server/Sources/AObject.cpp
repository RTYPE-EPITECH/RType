#include "AObject.hpp"
#include "Game.hpp"
#include <map>
#include <iostream>

AObject::AObject(Protocole & _p) : _proto(_p)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	type = UNKNOWN_OBJECT;
	id = _ids.size();
	_ids.push_back(id);
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

void	AObject::moveRight(size_t &x , size_t & y, size_t s) const
{
	x += s;
}

void	AObject::moveLeft(size_t &x, size_t &y, size_t s) const
{
	x -= s;
}

void	AObject::moveTop(size_t &x, size_t &y, size_t s) const
{
	y -= s;
}
void	AObject::moveBot(size_t &x, size_t &y, size_t s) const
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
	static size_t fx = x;
	static size_t fy = y;
	if (check == true) {
		tomove[UP] = &AObject::moveTop;
		tomove[DOWN] = &AObject::moveBot;
		tomove[LEFT] = &AObject::moveLeft;
		tomove[RIGHT] = &AObject::moveRight;
		check = false;
	}
	(this->*tomove[a])(fx, fy, t);

	// CHECK IF IT GET OUT OF SCREEN /!\ 

	// Check collision with Player/ScreenEdge. If true, then do nothing
	if (g->checkCollisionObject("Player", this)
		|| g->checkCollisionObject("Screen", this))
		return true;

	// check collision with enemies/obstacle/missile . If true, then player dies
	if (g->checkCollisionObject("Monster", this)
		|| g->checkCollisionObject("Obstacle", this)
		|| g->checkCollisionObject("Missile", this))
		return false;
	// no collision, apply position
	x = fx;
	y = fy;
	return true;
}