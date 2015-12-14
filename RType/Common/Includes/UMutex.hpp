#ifndef		UMUTEX_HPP
# define		UMUTEX_HPP

#include		"IMutex.hpp"
#include		<pthread.h>
#include		<iostream>
#include 	<exception>

class UMutex : public IMutex
{
private:
	pthread_mutex_t _mutex;
public:
	UMutex();
	virtual ~UMutex();
	virtual bool	initialize();
	virtual bool	lock();
	virtual void	unlock();
};

#endif		/* UMUTEX_HPP */
