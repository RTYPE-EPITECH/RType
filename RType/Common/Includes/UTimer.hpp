#ifndef UTIMER_HPP_
# define UTIMER_HPP_

#include "ITimer.hpp"

class UTimer : public ITimer
{
private:
	unsigned long long _start;
public:
	UTimer();
	virtual ~UTimer();
	virtual void   start();
	virtual unsigned long long getElapsedTimeInSec();
	virtual unsigned long long getElapsedTimeInMicroSec();
};

#endif /* UTIMER_HPP_ */
