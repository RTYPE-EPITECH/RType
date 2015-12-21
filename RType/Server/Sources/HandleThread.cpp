#include <iostream>
#include "HandleThread.hpp"
#include "Game.hpp"
#ifdef _WIN32
# include "WThread.hpp"
#else
# include "UThread.hpp"
#endif

HandleThread::HandleThread()
{
#ifdef _WIN32
	_t = new WThread();
#else
	_t = new UThread();
#endif
}

HandleThread::~HandleThread()
{
	delete (_t);
}

bool HandleThread::init(Game * cl)
{

	try {
		cl->setIdThread(_t->initialize(functionClient, static_cast<void*>(cl)));
	}
	catch (const std::runtime_error & msg)
	{
		std::cerr << "[Error HandleThread]" << msg.what() << std::endl;
		return false;
	}
	return true;
}

bool HandleThread::destroy(Game * cl)
{
	return _t->destroy(cl->getIdThread());
}

bool HandleThread::destroyAll()
{
	return _t->destroyAll();
}

void * HandleThread::functionClient(void * arg)
{
	Game * cl = reinterpret_cast<Game *>(arg);
	(void)cl;
	// Boucle du jeu
	cl->loop();
	return arg;
}
