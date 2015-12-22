#include "WConditionVariable.hpp"

WConditionVariable::WConditionVariable()
{
	condition = true;
}

WConditionVariable::~WConditionVariable()
{

}

bool WConditionVariable::init()
{
	InitializeConditionVariable(&ConditionVar);
	InitializeCriticalSection(&CritSection);
	return true;
}

void WConditionVariable::wait()
{
	EnterCriticalSection(&CritSection);
	condition = false;
	while (condition == false)
		SleepConditionVariableCS(&ConditionVar, &CritSection, INFINITE);
	LeaveCriticalSection(&CritSection);
}

void WConditionVariable::wait(unsigned long long t)
{
	EnterCriticalSection(&CritSection);
	condition = false;
	while (condition == false)
		SleepConditionVariableCS(&ConditionVar, &CritSection, (DWORD)(t / (unsigned long long)1000.0));
	LeaveCriticalSection(&CritSection);
}

void WConditionVariable::sendSignal(bool c)
{
	EnterCriticalSection(&CritSection);
	condition = c;
	LeaveCriticalSection(&CritSection);
	WakeAllConditionVariable(&ConditionVar);
}