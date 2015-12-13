#include "UConditionVariable.hpp"
#include <stdexcept>
#include <iostream>
#include <sys/time.h>

UConditionVariable::UConditionVariable()
{
	condition = true;
}

UConditionVariable::~UConditionVariable()
{
}

bool UConditionVariable::init()
{
	if (pthread_mutex_init(&_mut, NULL) != 0)
	{
		std::cerr << "[VariableCondition] Failed to initialize mutex" << std::endl;
		return false;
	}
	if (pthread_cond_init(&_cond, NULL) != 0)
	{
		std::cerr << "[VariableCondition] Failed to initialize variable cond" << std::endl;
		return false;
	}
	return true;
}

void UConditionVariable::wait()
{
	if (pthread_mutex_lock(&_mut) != 0)
		throw std::runtime_error("Failed to lock Mutex");
	while (condition == false)
		 if (pthread_cond_wait(&_cond, &_mut) != 0)
		 	throw std::runtime_error("Failed to wait cond var");
	if (pthread_mutex_unlock(&_mut) != 0)
		throw std::runtime_error("Failed to wait cond var");
}

void UConditionVariable::wait(unsigned long long t)
{
	struct timespec timeToWait;
	struct timeval now;

	gettimeofday(&now, NULL);
	timeToWait.tv_sec = now.tv_sec + t / 1000.0;
	timeToWait.tv_nsec = now.tv_usec * 1000;

	if (pthread_mutex_lock(&_mut) != 0)
		throw std::runtime_error("Failed to lock Mutex");
	while (condition == false)
		if (pthread_cond_timedwait(&_cond, &_mut, &timeToWait) != 0)
			throw std::runtime_error("Failed to wait cond var");
	if (pthread_mutex_unlock(&_mut) != 0)
		throw std::runtime_error("Failed to wait cond var");
}

void UConditionVariable::sendSignal(bool c)
{
	if (pthread_mutex_lock(&_mut) != 0)
		throw std::runtime_error("Failed to lock Mutex");
	condition = c;
	if (pthread_cond_broadcast(&_cond) != 0)
		throw std::runtime_error("Failed to broadcast signal");
	//pthread_cond_signal --> Only one thread 'll be unlock
	if (pthread_mutex_unlock(&_mut) != 0)
		throw std::runtime_error("Failed to unlock Mutex");
}
