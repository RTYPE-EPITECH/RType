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

void				Network::init(char *ip, int port) {
	_socket->_socket(SOCK_DGRAM);
	std::cout << "socket ok" << std::endl;
	_socket->_connect(ip, port);
	std::cout << "connect ok" << std::endl;
	_socket->_FD_ZERO("rw");
}

void				Network::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
}

bool				Network::readServer(void) {
	try {
		_socket->_recv(0);
	}
	catch (const std::exception) {
		//	deleteClient(i);
	}
	return true;
}

void				Network::writeServer(void) {
	std::cout << "Write on server : test" << std::endl;
	_socket->_send("test\n", 0);
	return;
}

void				Network::run(void) {
	while (true) {
		setClient();
		_socket->_select(60, 0);

		if (_socket->_FD_ISSET('w') == true)
			writeServer();
		if (_socket->_FD_ISSET('r') == true)
			if (readServer() == false)
				return;
	}
}
