#include		"UMutex.hpp"

UMutex::UMutex() {
}

UMutex::~UMutex() {
 if (pthread_mutex_destroy(&_mutex) != 0)
 	throw std::runtime_error("Failed to destroy mutex");
}

bool	UMutex::initialize()
{
	if (pthread_mutex_init(&_mutex, NULL) != 0){
        std::cerr << "[Error] Failed to init mutex" << std::endl;
        return false;
    }
    return true;
}

bool	UMutex::lock()
{
	pthread_mutex_lock(&_mutex);
	return true;
}

void	UMutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}
