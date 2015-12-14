#ifndef		UTHREAD_HPP_
# define		UTHREAD_HPP_
# define		MAX_THREAD 255

#include		"IThread.hpp"
#include		<pthread.h>
#include		<iostream>
#include		<exception>

class UThread : public IThread {
private:
	unsigned int maxIdThread;
	unsigned int nbThread;
	void * pDataArray[MAX_THREAD];
	pthread_t * idThread[MAX_THREAD];
public:
	UThread();
	virtual ~UThread();
	virtual unsigned int initialize(void *(*)(void *), void*);
	virtual bool join();
	virtual bool wait(unsigned int);
	virtual bool destroy(unsigned int);
	virtual bool destroyAll();
};

#endif		/* THREAD_HPP_ */
