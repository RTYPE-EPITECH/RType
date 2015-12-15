#include			"Network.hpp"
#include			<iostream>
#include			"Tools.hpp"
#include			"Client.hpp"
#include			"Game.hpp"

#ifdef _WIN32
# include			"WConditionVariable.hpp"
#else
# include			"UConditionVariable.hpp"
#endif

/*
** Constructeurs & Destructeurs
*/

Network::Network(void) {
	_socket = NULL;
}

Network::~Network(void) {
	if (_socket != NULL)
		delete _socket;
}

/*
** Méthodes
*/

void				Network::newClient(void) {
	std::cout <<  "A new client try to connect to the server..." << std::endl;
	Client * newClient = new Client();
	ISocket * newSocket = NULL;
	newClient->setSocket(_socket->_accept());

	// Trouver une game pour lui
	bool check = true;
	for (size_t i = 0; i < _games.size() && check; i++)
		if (_games[i]->getSizeAvailable() != 0)
		{
			newClient->init(_games[i]);
			_games[i]->addClient(newClient);
			check = false;
		}
	// Si aucune game OK : CReate a game
	if (check)
		createGame(newClient);
}

void				Network::deleteClient(unsigned int i) {
(void)i;
#ifdef _WIN23
	std::cout << CYAN << HIGHLIGHT << "Client disconnect (fd : " << _clients[i]->getSocket()->getfd() << ")" << std::endl;
#else
	std::cout << CYAN << HIGHLIGHT << "Client disconnect" << std::endl;
#endif
	_games[findGame(_clients[i])]->removeClient(_clients[i]);
}

size_t				Network::findGame(Client *c)
{
	for (size_t i = 0; i < _games.size(); i++)
		if (_games[i]->getIdThread() == c->getIdThreadGame())
			return i;
	throw std::runtime_error("[Network] Cannot find game");
	return 0;
}

void				Network::init(const std::string & port) {
#ifdef WIN32
	_socket = new WSocket();
	_i = new WConditionVariable();
#else
	_socket = new USocket();
	_i = new UConditionVariable();
#endif
	_socket->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	//_socket->_socket(ISocket::IPv4, ISocket::DGRAM, ISocket::UDP);
	std::cout << "socket ok" << std::endl;
	_socket->_bind(ISocket::IPv4, Tools::charToNumber<unsigned short>(port));
	std::cout << "bind ok" << std::endl;
	_socket->_FD_ZERO("rw");
	std::cout << "Welcome on the RType Server (port : " << port.c_str() << ")" << std::endl;
}

void				Network::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
	for (unsigned int i = 0; i < _clients.size(); i++) {
		_socket->_FD_SET(_clients[i]->getSocket(), "r");
		if (_clients[i]->getOutput() != NULL)
			_socket->_FD_SET(_clients[i]->getSocket(), "w");
	}
}

bool				Network::readClient(unsigned int i) {
(void)i;
	try {
		//_listClient[i]->_receive();
	}
	catch (const std::exception) {
		deleteClient(i);
	}
	return true;
}

void				Network::writeClient(unsigned int i) {
(void)i;
	//_listClient[i]->_send();
	return;
}

void				Network::createGame(Client * e)
{
	Game * g = new Game(*_i);
	g->init(_init);
	e->init(g);
	_handle.init(g);
	g->addClient(e);
	_games.push_back(g);
}

void				Network::run(void)
{
	while (true) {
		setClient();
		_socket->_select(60, 0);
		std::cout << "Selected passed" << std::endl;
		/* Nouveau Client */
		if (_socket->_FD_ISSET('r') == true)
			newClient();
		else
		{
			for (unsigned int i = 0; i < _clients.size(); i++) {
				if (_socket->_FD_ISSET(_clients[i]->getSocket(), 'w') == true)
					writeClient(i);
				if (_socket->_FD_ISSET(_clients[i]->getSocket(), 'r') == true)
					if (readClient(i) == false)
						return;
			}
		}
	}
}