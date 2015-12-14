#ifndef TIMER_HPP_
# define TIMER_HPP_

#include <windows.h>
#include "ITimer.hpp"

class WTimer : public ITimer
{
public:
	WTimer();
	virtual ~WTimer();
	virtual void   start();
	virtual unsigned long long getElapsedTimeInSec();
	virtual unsigned long long getElapsedTimeInMicroSec();

private:
	LONGLONG startTimeInNanoSec;
	LONGLONG endTimeInNanoSec;
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
};

#endif /* TIMER_HPP_ */