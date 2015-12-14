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
	return getElapsedTimeInMicroSec() / 1000.0;
}

unsigned long long UTimer::getElapsedTimeInMicroSec()
{
	unsigned long long now = std::time(0);
	now -= _start;
	_start = std::time(0);
	return now;
}
