#include "AObject.hpp"
#include "Game.hpp"
#include <map>
#include <iostream>
#include "Missile.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Tools.hpp"

std::vector<size_t> AObject::_ids;

AObject::AObject(void)
{
	x = 5;
	y = 5;
	width = 1;
	height = 1;
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
	if (x + width + s < WIDTH)
		x += s;
}

void	AObject::moveLeft(size_t &x, size_t &, size_t s) const
{
	if (x - s > 0)
		x -= s;
}

void	AObject::moveTop(size_t &, size_t &y, size_t s) const
{
	if (y - s > 0)
		y -= s;
}
void	AObject::moveBot(size_t &, size_t &y, size_t s) const
{
	if (y + height + s < HEIGHT)
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
	if (isDead())
		return false;
  if (getType() == PLAYER)
  {
	  Player * p = reinterpret_cast<Player *>(this);
	  if (p->canMove() == false)
	  {
	  	return false;
	  	}
  }

  (this->*tomove[a])(fx, fy, t);

if (getType() == PLAYER)
  {
	  if (fx < ZONE - width)
	  	fx = ZONE - width + 1;
		if (fx + width > SPAWN)
		fx = SPAWN - width - 1;
	}

  // Check collision with Player/ScreenEdge. If true, then do nothing
  if (g->checkCollisionObject("Player", this) != NULL)
    return true;


  // check collision with enemies/obstacle/missile . If true, then player dies
  AObject * e;
  if ((e = g->checkCollisionObject("Objects", this))!= NULL)
    {
    	die(g);
    	if (type == MISSILE)
      	e->die(g);
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
	else
		die(g);
      o->die(g);
    }
  if (fx < ZONE - width)
	  die(g);
	if (fx + width >= WIDTH)
		die(g);
  if (isDead())
    return false;
  // no collision, apply position
  x = fx;
  y = fy;
  g->_proto._addPositionPacket((unsigned int)fx, (unsigned int)fy,
	  (unsigned int)width, (unsigned int)height, (EObject)type, (Tools::getName(type, id)).c_str() , "unknown");
  return true;
}

void	AObject::die(Game *g)
{
	std::cout << "[DIE] create Packet die" << std::endl;
	_proto._createDeadEntityPacket(type, (Tools::getName(type, id)).c_str());
	g->addPacketForClients(_proto._getLastPacket(), true);
	_dead = true;
}
