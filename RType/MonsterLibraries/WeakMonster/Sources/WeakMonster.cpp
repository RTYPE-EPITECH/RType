#include "WeakMonster.hpp"

WeakMonster::WeakMonster(void) : Monster() {
	this->maxLife = 5;
	this->life = this->maxLife;
	this->maxMissile = 1;
	this->currentMissile = this->maxMissile;
	this->typeMissile = ONESHOT;
}

WeakMonster::~WeakMonster(void) {}

