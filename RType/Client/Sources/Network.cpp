#include			"Network.hpp"

/*
** Constructeurs & Destructeurs
*/

Network::Network(void) {
#ifdef _WIN32
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

void				Network::init(const char *ip, int port) {
	_game = new Game();
	_game->init();
	_socket->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	std::cout << "New socket ok" << std::endl;
	Sleep(1000);
	_socket->_connect(ISocket::IPv4, ip, port);
	std::cout << "connext ok" << std::endl;
	Sleep(1000);
}

void				Network::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
	if (_game->getOutput().size() != 0) {
		std::cout << "Set Select en écriture" << std::endl;
		_socket->_FD_SET("w");
	}
}

bool				Network::readServer(void) {
	std::cout << "read server" << std::endl;
	_game->addInput(_socket->_recv(0));
	return true;
}

void				Network::writeServer(void) {
	std::cout << "write server" << std::endl;
	std::vector<char *> listOutput = _game->getOutput();
	for (unsigned int i = 0; i < listOutput.size(); i++)
		_socket->_send(listOutput[i], 0);
	return;
}

void				Network::run(void) {
	while (true) {
		setClient();
		std::cout << "client set" << std::endl;
		_socket->_select(60, 0);
		std::cout << "select set" << std::endl;
		if (_socket->_FD_ISSET('w') == true)
			writeServer();
		if (_socket->_FD_ISSET('r') == true)
			if (readServer() == false)
				return;
	}
}
