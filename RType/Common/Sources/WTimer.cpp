#include "WTimer.hpp"

WTimer::WTimer()
{
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;
	startTimeInNanoSec = 0;
	endTimeInNanoSec = 0;
}

WTimer::~WTimer()
{
}


void WTimer::start()
{
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;
	startTimeInNanoSec = 0;
	endTimeInNanoSec = 0;
	QueryPerformanceCounter(&startCount);
}

unsigned long long WTimer::getElapsedTimeInMicroSec()
{
	QueryPerformanceCounter(&endCount);
	startTimeInNanoSec = startCount.QuadPart;// *(1000000000.0 / frequency.QuadPart);
	endTimeInNanoSec = endCount.QuadPart; // *(1000000000.0 / frequency.QuadPart);
	return endTimeInNanoSec - startTimeInNanoSec;
}

unsigned long long WTimer::getElapsedTimeInSec()
{
	return this->getElapsedTimeInMicroSec() / (unsigned long)1000000;
}