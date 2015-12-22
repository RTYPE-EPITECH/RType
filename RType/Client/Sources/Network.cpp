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
}

Network::~Network(void) {
	delete _socket;
}

/*
** Méthodes
*/

void				Network::init(const char *ip, int port) {
	_socket->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);

  std::cout << "New socket ok" << std::endl;
#ifdef _WIN32
  Sleep(1000);
#endif
  _socket->_connect(ISocket::IPv4, ip, port);
  std::cout << "connext ok" << std::endl;
#ifdef _WIN32
  Sleep(1000);
#endif
  _game = new Game();
  if (_game->init() == false)
	  throw std::runtime_error("Failed to launch Game");
}

void				Network::setClient(void) {
	_socket->_FD_ZERO("rw");
	_socket->_FD_SET("r");
	if (_game->haveOutput()) {
		std::cout << "FD SET Write" << std::endl;
		_socket->_FD_SET("w");
	}
}

bool				Network::readServer(void) {
	char * header = NULL;
	char * body = NULL;
	std::cout << "read server" << std::endl;
	//header = _socket->_recv(_proto.);

	
	_game->addInput(NULL);
	return true;
}

void				Network::writeServer(void) {

	std::vector<char *> listOutput = _game->getOutput();
	std::cout << "Write server (" << listOutput.size() << " packets)" << std::endl;
	for (unsigned int i = 0; i < listOutput.size(); i++)
		_socket->_send(listOutput[i], _proto._getSizePacket(listOutput[i]), 0);
	return;
}

void				Network::run(void) {
	while (true) {
		setClient();
		std::cout << "client set" << std::endl;
		int tmp = (int)(1.0 / 30.0 * 1000.0);
		std::cout << "Select (Timeout : " << tmp << " ms)" << std::endl;
		_socket->_select(5, tmp);
		if (_socket->_FD_ISSET('w') == true)
			writeServer();
		if (_socket->_FD_ISSET('r') == true)
			if (readServer() == false)
				return;
	}
}
