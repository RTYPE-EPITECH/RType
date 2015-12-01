#ifndef AOBJECT_HPP
#define AOBJECT_HPP

#include "Protocole.hpp"
#include "EObject.hpp"

class AObject
{
public:
	AObject(Protocole &);
	~AObject();

	// FAIRE LES GET/SET

private:
	size_t x;
	size_t y;
	size_t width;
	size_t height;
	EObject type;
	Protocole & _proto;
};



#endif /* AOBJECT_HPP */