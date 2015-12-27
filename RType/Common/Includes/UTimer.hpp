#ifndef UTIMER_HPP_
# define UTIMER_HPP_

#include "ITimer.hpp"

#include <sys/time.h>

class UTimer : public ITimer
{
private:
	unsigned long long _start;
	struct timeval _start_tv;
public:
	UTimer();
	virtual ~UTimer();
	virtual void   start();
	virtual unsigned long long getElapsedTimeInSec();
	virtual unsigned long long getElapsedTimeInMicroSec();
};

#endif /* UTIMER_HPP_ */
