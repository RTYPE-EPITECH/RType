#include "WThread.hpp"
#include <iostream>

WThread::WThread()
{
	maxIdThread = 0;
	nbThread = 0;
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		pDataArray[i] = NULL;
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		hThreadArray[i] = NULL;
}

WThread::~WThread()
{
}

unsigned int WThread::initialize(void * (*fc)(void*), void* data)
{
	unsigned int i = 0;
	for (i = 0; i < MAX_THREAD; i++)
		if (pDataArray[i] == NULL)
			break;
	if (i == MAX_THREAD)
		return false;
	pDataArray[i] = data;

	// Create the thread to begin execution on its own.

	hThreadArray[i] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		(LPTHREAD_START_ROUTINE)fc,       // thread function name
		pDataArray[i],          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray[i]);   // returns the thread identifier 

	if (hThreadArray[i] == NULL)
	{
		std::cerr << "Failed to create Thread" << std::endl;
		return false;
	}
	if (i == nbThread)
		maxIdThread++;
	nbThread++;
	return dwThreadIdArray[i];
}

bool WThread::join()
{
	WaitForMultipleObjects(MAX_THREAD, hThreadArray, FALSE, INFINITE);
	return true;
}

bool WThread::wait(unsigned int j)
{
	unsigned int i = 0;
	for (i = 0; i < MAX_THREAD; i++)
		if (dwThreadIdArray[i] == j)
			break;
	WaitForSingleObject(hThreadArray[i], INFINITE);
	return true;
}

bool WThread::destroy(unsigned int j)
{
	unsigned int i = 0;
	for (i = 0; i < MAX_THREAD; i++)
		if (j == dwThreadIdArray[i])
			break;
	CloseHandle(hThreadArray[i]);
	if (pDataArray[i] != NULL)
	{
		pDataArray[i] = NULL;
		hThreadArray[i] = NULL;
		nbThread--;
		return true;
	}
	return false;

}

bool WThread::destroyAll()
{
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		if (pDataArray[i] != NULL)
			destroy(dwThreadIdArray[i]);
	maxIdThread = 0;
	nbThread = 0;
	return true;
}
