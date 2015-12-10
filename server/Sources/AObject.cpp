#include "AObject.hpp"
#include <map>

AObject::AObject(Protocole & _p) : _proto(_p)
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	type = UNKNOWN_OBJECT;
}

AObject::~AObject()
{
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

bool	AObject::move(ACTION a, size_t t)
{
	static std::map<ACTION,
					void(AObject::*)(size_t &, 
									size_t &, 
									size_t) const> tomove;
	static bool check = true;
	static size_t fx = x;
	static size_t fy = y;
	if (check == true) {
		tomove[UP] = &moveTop;
		tomove[DOWN] = &moveBot;
		tomove[LEFT] = &moveLeft;
		tomove[RIGHT] = &moveRight;
	}
	(this->*tomove[a])(fx, fy, t);
// a finir;
}