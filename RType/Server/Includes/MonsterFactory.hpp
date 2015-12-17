#pragma once
#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

#include <map>
#include <stdexcept>
#include <vector>
#include "IDynamicLibrary.hpp"
#include "IMonster.hpp"

class Monster;

class MonsterFactory
{
public:
	static MonsterFactory * getInstance();
	~MonsterFactory();
	bool addLibrary(const std::string &);
	Monster *	getInstance(const std::string &);
	std::vector<std::string> & getAllMonsterName();
private:
	MonsterFactory();
	MonsterFactory & operator=(const MonsterFactory &);
	MonsterFactory(const MonsterFactory &);
	std::map<std::string, IDynamicLibrary<IMonster*> *> gen;
	std::vector<std::string> _listMonster;
};

#endif // MONSTERFACTORY_HPP_