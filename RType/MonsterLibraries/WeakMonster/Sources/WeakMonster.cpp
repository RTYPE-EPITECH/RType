#include "WeakMonster.hpp"

WeakMonster::WeakMonster(void){
}

WeakMonster::~WeakMonster(void) {}

size_t WeakMonster::getLife() const
{
	return 5;
}

size_t WeakMonster::getMaxLife() const
{
	return 5;
}

size_t WeakMonster::getMaxMissile() const
{
	return 1;
}

EMissile WeakMonster::getTypeMissile() const
{
	return ONESHOT;
}

std::string WeakMonster::getTypeMonster() const
{
	return "WeakMonster";
}