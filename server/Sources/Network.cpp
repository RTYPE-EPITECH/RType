#include			"Network.hpp"
#include			<iostream>
#include			"Tools.hpp"
#include			"Client.hpp"
#include			"Game.hpp"

#ifdef WIN32
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

	//ISocket * New = _socket->_accept();

}

void				Network::deleteClient(unsigned int i) {
(void)i;
	//std::cout << CYAN << HIGHLIGHT << "Client disconnect (fd : " << _listClient[i]->getSocket()->getfd() << ")" << std::endl;
	//delete _listClient[i];
	//_listClient.erase(_listClient.begin() + i);
}

void				Network::init(const std::string & port) {
#ifdef WIN32
	_socket = new WSocket();
	_i = new WConditionVariable();
#else
	_socket = new USocket();
	_i = new UConditionVariable();
#endif

	_socket->_socket(ISocket::IPv4, ISocket::DGRAM, ISocket::TCP);
	std::cout << "socket ok" << std::endl;
	_socket->_bind(ISocket::IPv4, Tools::charToNumber<unsigned short>(port));
	std::cout << "bind ok" << std::endl;

	_socket->_FD_ZERO("rw");
	std::cout << "Welcome on the RType Server (port : " << port.c_str() << ")" << std::endl;
}

void				Network::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
	/*for (unsigned int i = 0; i < _listClient.size(); i++) {
		_socket->_FD_SET(_listClient[i]->getSocket(), "r");
		if (_listClient[i]->getInput()->_getListMsg().size() != 0)
			_socket->_FD_SET(_listClient[i]->getSocket(), "w");
	}*/
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

void				Network::run(void) {
	while (true) {
		setClient();
		_socket->_select(60, 0);
		std::cout << "bite" << std::endl;
		/* Nouveau Client */
		if (_socket->_FD_ISSET('r') == true)
			newClient();
		else
		{
		}
			/*for (unsigned int i = 0; i < _listClient.size(); i++) {
				if (_socket->_FD_ISSET(_listClient[i]->getSocket(), 'w') == true)
					writeClient(i);
				if (_socket->_FD_ISSET(_listClient[i]->getSocket(), 'r') == true)
					if (readClient(i) == false)
						return;
			}*/
	}
}
