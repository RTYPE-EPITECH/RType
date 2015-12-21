#ifndef WMUTEX_H_
#define WMUTEX_H

#include "IMutex.hpp"
//#include <windows.h>
#include <mutex>


class WMutex : public IMutex
{
private:	
	//HANDLE ghMutex;
	std::mutex mtx;
public:
	WMutex();
	virtual ~WMutex();
	virtual bool	initialize();
	virtual bool	lock();
	virtual void	unlock();
};

#endif // !WMUTEX_H_