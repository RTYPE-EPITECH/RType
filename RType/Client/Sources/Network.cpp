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
	_socket->_connect(ISocket::IPv4, ip, port);std::cout << "connext ok" << std::endl;
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
	try {
		if (_game->getState() < POSITION_PACKET_SET)
		{
			std::cout << "try to read header..." << std::endl;
			header = _socket->_recv(_proto._getSizePacketHeader(), 0);
			if (header == NULL) {
				std::cerr << RED << "Fail to read (TCP) header" << WHITE << std::endl;
				return false;
			}
			_proto._setNewPacketHeader(header);
			if (_proto._getHeaderSize() != 0) {
				std::cout << "try to read body of size " << _proto._getHeaderSize() << std::endl;
				body = _socket->_recv(_proto._getHeaderSize(), 0);
				if (body == NULL) {
					std::cerr << RED << "Fail to read (TCP) body packet" << WHITE << std::endl;
					return false;
				}
			}
			std::cout << "Packet correctly read" << std::endl;
		}
/*		else
		{
			ISocket::tSocketAdress add;
			header = _socket->_recvfrom((unsigned int)_proto._getSizePacketHeader(), 0, &add);
			if (header == NULL) {
				std::cerr << RED << "Fail to read (UDP) header" << WHITE << std::endl;
				return false;
			}
			_proto._setNewPacketHeader(header);
			body = _socketConnexion->_recvfrom((unsigned int)_proto._getHeaderSize(), 0, &add);
			if (body == NULL) {
				std::cerr << RED << "Fail to read (UDP) body packet" << WHITE << std::endl;
				return false;
			}
			short id = _proto._getHeaderId();
			for (size_t j = 0; j < _clients.size(); j++)
				if (_clients[j]->getPlayer()->getId() == (size_t)id)
				{
					i = (unsigned int)j;
					break;
				}
			memcpy(&(_clients[i]->_adr), &add, sizeof(ISocket::tSocketAdress));
		}*/
		const char * packet = _proto._linkPacketHeaderBody(header, body);
		_game->addInput(packet);
	}
	catch (const std::runtime_error & e) {
//		deleteClient(i);
		std::cerr << "[Read Server]" << e.what() << std::endl;
	}
	return true;
}

void				Network::writeServer(void) {

	std::vector<const char *> listOutput = _game->getOutput();
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
