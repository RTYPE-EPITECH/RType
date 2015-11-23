#include			"Network.hpp"

/*
** Constructeurs & Destructeurs
*/

Network::Network(void) {
#ifndef WIN32
	_socket = new USocket();
#else
	_socket = new WSocket();
#endif
	//_listClient.clear();
}

Network::~Network(void) {
	delete _socket;
}

/*
** Méthodes
*/

void				Network::newClient(void) {
	//_listClient.push_back(new Client(_socket->_accept()));
	std::cout << CYAN << HIGHLIGHT << "A new client try to connect to the server..." << DEFAULT << std::endl;
}

void				Network::deleteClient(unsigned int i) {
	std::cout << CYAN << HIGHLIGHT << "Client disconnect (fd : " << _listClient[i]->getSocket()->getfd() << ")" << std::endl;
	//delete _listClient[i];
	//_listClient.erase(_listClient.begin() + i);
}

void				Network::init(char *port) {
	_socket->_socket(AF_INET, SOCK_STREAM, 0);
	_socket->_bind(AF_INET, atoi(port));
	_socket->_listen(2147483647);
	_listClient.push_back(new Client(new USocket(STDIN_FILENO)));
	_socket->_FD_ZERO("rw");
	std::cout << PURPLE << HIGHLIGHT << "Welcome on the Spider Server (port : " << port << ")" << DEFAULT << std::endl;
}

void				Server::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
	for (unsigned int i = 0; i < _listClient.size(); i++) {
		_socket->_FD_SET(_listClient[i]->getSocket(), "r");
		if (_listClient[i]->getInput()->_getListMsg().size() != 0)
			_socket->_FD_SET(_listClient[i]->getSocket(), "w");
	}
}

bool				Server::readClient(unsigned int i) {
	try {
		if (i > 0) {
			_listClient[i]->_receive();
			if (_listClient[i]->_getMac()) {
				_listClient[i]->getInput()->_writeLog();
			}
		}
		else {
			std::string cmd;
			cmd = _listClient[i]->getSocket()->_readCmd();
			if (cmd == "shutdown")
				return false;
			else
				std::cerr << "[Error]: Command not found" << std::endl;
		}
	}
	catch (const std::exception) {
		deleteClient(i);
	}
	return true;
}

void				Server::writeClient(unsigned int i) {
	_listClient[i]->_send();
	return;
}

void            Server::run(void) {
	while (true) {
		setClient();
		_socket->_select(60, 0);

		/* Nouveau Client */
		if (_socket->_FD_ISSET('r') == true)
			newClient();
		else
			for (unsigned int i = 0; i < _listClient.size(); i++) {
				if (_socket->_FD_ISSET(_listClient[i]->getSocket(), 'w') == true)
					writeClient(i);
				if (_socket->_FD_ISSET(_listClient[i]->getSocket(), 'r') == true)
					if (readClient(i) == false)
						return;
			}
	}
}
