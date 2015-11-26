#include "AObject.hpp"

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

