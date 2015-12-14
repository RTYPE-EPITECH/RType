#include "UThread.hpp"
#include <stdexcept>

UThread::UThread()
{
	maxIdThread = 0;
	nbThread = 0;
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		pDataArray[i] = NULL;
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		idThread[i] = NULL;
}

UThread::~UThread()
{
	for (unsigned int i = 0; i < MAX_THREAD; i++) {
		if (idThread[i] != NULL)
			delete(idThread[i]);
	}
}

unsigned int UThread::initialize(void *(*fc)(void *), void* arg)
{
	unsigned int i = 0;
	for (i = 0; i < MAX_THREAD; i++)
		if (idThread[i] == NULL)
			break;
	if (i == MAX_THREAD)
		return false;
	pDataArray[i] = arg;
	idThread[i] = new pthread_t;
	if (pthread_create(idThread[i], NULL, fc, arg) != 0)
		throw std::runtime_error("Failed to create UNIX Thread");
	return i;
}

bool UThread::join()
{
	bool error = true;
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		if (idThread[i] != NULL)
			if (pthread_join(*idThread[i], NULL) != 0)
				error = false;
	if (!error)
		std::cerr << "Failed to join UNIX Thread" << std::endl;
	return error;
}

bool UThread::wait(unsigned int id)
{
	if (idThread[id] != NULL)
 		if (pthread_join(*idThread[id], NULL) != 0) {
 			std::cerr << "Failed to join UNIX Thread" << std::endl;
			return false;
 		}
 	return true;
}

bool UThread::destroy(unsigned int id)
{
	if (idThread[id] != NULL)
		if (pthread_cancel(*idThread[id]) != 0) {
			std::cerr << "Failed to cancel UNIX Thread" << std::endl;
			return false;
		}
	delete(idThread[id]);
	idThread[id] = NULL;
	return true;
}

bool UThread::destroyAll()
{
	bool error = true;
	for (unsigned int i = 0; i < MAX_THREAD; i++)
		if (idThread[i] != NULL)
		{
			if (pthread_cancel(*idThread[i]) != 0) {
				std::cerr << "Failed to cancel UNIX Thread" << std::endl;
				error = false;
			}
			delete(idThread[i]);
			idThread[i] = NULL;
		}
	return error;
}
