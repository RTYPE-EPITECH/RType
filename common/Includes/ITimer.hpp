#ifndef ITIMER_HPP_
# define ITIMER_HPP_

class ITimer
{
public:
	virtual ~ITimer() {}
	virtual void   start() = 0;
	virtual unsigned long long getElapsedTimeInSec() = 0;
	virtual unsigned long long getElapsedTimeInMicroSec() = 0;
};

#endif /* ITIMER_HPP_ */