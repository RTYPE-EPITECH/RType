#pragma once
#ifndef IMONSTER_HPP_
# define IMONSTER_HPP_

#include "EMissile.hpp"
#include <string>

class IMonster
{
public:
	virtual ~IMonster() {}
	virtual size_t getLife() const = 0;
	virtual size_t getMaxLife() const = 0;
	virtual size_t getMaxMissile() const = 0;
	virtual EMissile getTypeMissile() const = 0;
	virtual std::string getTypeMonster() const = 0;
};

#endif // IMONSTER_HPP_
