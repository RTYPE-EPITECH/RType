#include "Obstacle.hpp"

Obstacle::Obstacle(void) : AObject()
{
	type = OBSTACLE;
	width = 32;
	height = 32;
}

Obstacle::~Obstacle()
{
}
