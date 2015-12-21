#include "WMutex.hpp"
#include <iostream>

WMutex::WMutex()
{
}

WMutex::~WMutex()
{
	CloseHandle(ghMutex);
}

 bool	WMutex::initialize()
{
	ghMutex = CreateMutex(NULL, FALSE, NULL);
	if (ghMutex == NULL)
	{
		std::cerr << "Error while creating mutex" << std::endl;
		return false;
	}
	return true;
}

 bool	WMutex::lock()
{
	std::cout << "LOCK" << std::endl;
	DWORD dwWaitResult = WaitForSingleObject(
		ghMutex,    // handle to mutex
		INFINITE);  // no time-out interval
	std::cout << dwWaitResult << std::endl;
	std::cout << WAIT_OBJECT_0 << std::endl;
	switch (dwWaitResult)
	{
		case WAIT_OBJECT_0:
			std::cout << "Lock réussi " << std::endl;
			return true;
		default:
			std::cout << "Fail" << std::endl;
			return false;
	}
	std::cout << "Fail" << std::endl;
	return false;
}

 void	WMutex::unlock()
{
	std::cout << "unlock" << std::endl;
	if (!ReleaseMutex(ghMutex))
		throw std::runtime_error("Failed to unlock Mutex");
}