#pragma once
#ifndef WAVEMONSTERFACTORY_HPP
# define WAVEMONSTERFACTORY_HPP

#include "EObject.hpp"
#include <vector>

class AObject;

class WaveFactory
{
public:
	WaveFactory();
	~WaveFactory();

	void addItem(AObject *, size_t, size_t, size_t, size_t);
	void addItemNoPos(AObject *);
	void addObstacle();
	void addMonster(const std::string &);
	void addMonster();
	std::vector<AObject *> * getWaves();
	AObject * getLastItem();
private:
	std::vector<std::string> name;
	std::vector<AObject *> * _waves;
};

#endif // WAVEMONSTERFACTORY_HPP