#ifndef UCONDITIONVARIABLE_HPP_
# define UCONDITIONVARIABLE_HPP_

#include <pthread.h>

class UConditionVariable
{
private:
	pthread_cond_t _cond;
	pthread_mutex_t _mut;
	bool condition;
public:
	UConditionVariable();
	virtual ~UConditionVariable();
	virtual bool init();
	virtual void wait();
	virtual void sendSignal(bool c = true);
};

#endif /* UCONDITIONVARIABLE_HPP_ */
