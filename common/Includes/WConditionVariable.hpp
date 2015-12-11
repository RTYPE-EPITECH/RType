#pragma once
#ifndef WCONDITIONVARIABLE_HPP_
# define WCONDITIONVARIABLE_HPP_

#include "IConditionVariable.hpp"
#include <Windows.h>

class WConditionVariable : public IConditionVariable
{
private:
	CRITICAL_SECTION CritSection;
	CONDITION_VARIABLE ConditionVar;
	bool condition;
public:
	WConditionVariable();
	virtual ~WConditionVariable();
	virtual bool init();
	virtual void wait();
	virtual void sendSignal(bool c = true);
};

#endif /* WCONDITIONVARIABLE_HPP_ */