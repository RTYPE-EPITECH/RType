#include "UTimer.hpp"
#include <ctime>

UTimer::UTimer()
{
}

UTimer::~UTimer()
{
}

void   UTimer::start()
{
	_start = std::time(0);
}

unsigned long long UTimer::getElapsedTimeInSec()
{
	unsigned long long now = std::time(0);
	now -= _start;
	return now;
}

unsigned long long UTimer::getElapsedTimeInMicroSec()
{
	return getElapsedTimeInSec() * 1000000.0;
}
