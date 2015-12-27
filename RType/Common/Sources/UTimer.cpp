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
	gettimeofday(&_start_tv,NULL);
}

unsigned long long UTimer::getElapsedTimeInSec()
{
	unsigned long long now = std::time(0);
	now -= _start;
	return now;
}

unsigned long long UTimer::getElapsedTimeInMicroSec()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);

	unsigned long now = 1000000 * tv.tv_sec + tv.tv_usec;
	unsigned long start = 1000000 * _start_tv.tv_sec + _start_tv.tv_usec;
	return now - start;
}
