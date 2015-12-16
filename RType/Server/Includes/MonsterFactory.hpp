#pragma once
#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

#include <map>
#include <stdexcept>
#include "IDynamicLibrary.hpp"

class Monster;

class MonsterFactory
{
public:
	MonsterFactory();
	~MonsterFactory();
	bool addLibrary(const std::string &);
	Monster *	getInstance(const std::string &);
private:
	std::map<std::string, IDynamicLibrary *> gen;
	
};

#endif // MONSTERFACTORY_HPP_