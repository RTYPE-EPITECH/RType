#include			"Network.hpp"

/*
** Constructeurs & Destructeurs
*/

Network::Network(void) {
#ifdef WIN32
	_socket = new WSocket();
#else
	_socket = new USocket();
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
	std::cout <<  "A new client try to connect to the server..." << std::endl;
}

void				Network::deleteClient(unsigned int i) {
	//std::cout << CYAN << HIGHLIGHT << "Client disconnect (fd : " << _listClient[i]->getSocket()->getfd() << ")" << std::endl;
	//delete _listClient[i];
	//_listClient.erase(_listClient.begin() + i);
}

void				Network::init(const std::string & port) {
	_socket->_socket(SOCK_DGRAM);
	std::cout << "socket ok" << std::endl;
	_socket->_bind(atoi(port.str()));
	std::cout << "bind ok" << std::endl;

	//_listClient.push_back(new Client(new USocket(STDIN_FILENO)));
	_socket->_FD_ZERO("rw");
	std::cout << "Welcome on the RType Server (port : " << port << ")" << std::endl;
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
	try {
		//_listClient[i]->_receive();
	}
	catch (const std::exception) {
		deleteClient(i);
	}
	return true;
}

void				Network::writeClient(unsigned int i) {
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
			/*for (unsigned int i = 0; i < _listClient.size(); i++) {
				if (_socket->_FD_ISSET(_listClient[i]->getSocket(), 'w') == true)
					writeClient(i);
				if (_socket->_FD_ISSET(_listClient[i]->getSocket(), 'r') == true)
					if (readClient(i) == false)
						return;
			}*/
			;
	}
}
