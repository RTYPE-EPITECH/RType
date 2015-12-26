#include "Player.hpp"
#include "Missile.hpp"
#ifdef _WIN32
#include "WTimer.hpp"
#else
#include "UTimer.hpp"
#endif
#include "Tools.hpp"
#include "Game.hpp"

Player::Player(void) : AObject()
{
	width = 100;
	height = 100;
	life = 10;
	maxLife = 10;
	maxMissile = 3;
	currentMissile = 0;
	typeMissile = NORMAL;
	type = PLAYER;
#ifdef _WIN32
	_tShoot = new WTimer();
	_tMove = new WTimer();
#else
	_tShoot = new UTimer();
	_tMove = new UTimer();
#endif
	_tShoot->start();
	_tMove->start();
}

Player::~Player() {
	delete (_tShoot);
	delete (_tMove);
}

Missile * Player::shoot(Game *g)
{
	if (_tShoot->getElapsedTimeInMicroSec() > SPEED_SHOT * 1000000)
	{
		currentMissile++;
		missiles.push_back(Missile::newInstance(typeMissile, x + width + 1, y + width / 2));
		// CREATE PACKET NEW SPRITE
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
		_tShoot->start();
		return missiles.back();
	}
	return NULL;
}

size_t Player::getLife() const
{
	return life;
}

size_t Player::getMaxLife() const
{
	return maxLife;
}

size_t Player::getMaxMissile() const
{
	return maxMissile;
}

EMissile Player::getTypeMissile() const
{
	return typeMissile;
}

void Player::setLife(size_t l)
{
	life = l;
}

void Player::setMaxLife(size_t l)
{
	maxLife = l;
}

void Player::setMaxMissile(size_t l)
{
	maxMissile = l;
}

void Player::setTypeMissile(EMissile t)
{
	typeMissile = t;
}

bool Player::canMove()
{
	if (_tMove->getElapsedTimeInMicroSec() > SPEED_MOVE * 1000000)
	{
		_tMove->start();
		return true;
	}
	return false;
}