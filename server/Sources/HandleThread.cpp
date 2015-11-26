#include <iostream>
#include "HandleThread.hpp"
#include "IThread.hpp"
#include "Client.hpp"

bool HandleThread::init(Client * cl)
{
	try {
		cl->setIdThread(_t->initialize(functionClient, static_cast<void*>(cl)));
	}
	catch (const std::exception & msg)
	{
		std::cerr << "[Error HandleThread]" << msg.what() << std::endl;
		return false;
	}
	return true;
}

bool HandleThread::destroy(Client * cl)
{
	return _t->destroy(cl->getIdThread());
}

bool HandleThread::destroyAll()
{
	return _t->destroyAll();
}

void * HandleThread::functionClient(void * arg)
{
	Client * cl = reinterpret_cast<Client *>(arg);

	// Boucle du jeu
	// cl->game->init();
	// cl->game->loop();
	return arg;
}