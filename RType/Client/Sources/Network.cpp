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

void				Network::init(const char *ip, int port) {
	_game = new Game();
	_socket->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	_socket->_connect(ISocket::IPv4, ip, port);
	_socket->_FD_ZERO("rw");
}

void				Network::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
}

bool				Network::readServer(void) {
	_game->addInput(_socket->_recv(0));
	return true;
}

void				Network::writeServer(void) {
	std::vector<char *> listOutput = _game->getOutput();
	for (unsigned int i = 0; i < listOutput.size(); i++)
		_socket->_send(listOutput[i], 0);
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
