#ifndef ICONDITIONVARIABLE_HPP_
# define ICONDITIONVARIABLE_HPP_

class IConditionVariable
{
public:
	virtual ~IConditionVariable() {}
	virtual bool init() = 0;
	virtual void wait() = 0;
	virtual void sendSignal() = 0;
};


#endif /* ICONDITIONVARIABLE_HPP_ */