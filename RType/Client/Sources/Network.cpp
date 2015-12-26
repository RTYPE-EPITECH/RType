#include			"Network.hpp"

/*
** Constructeurs & Destructeurs
*/

Network::Network(void) {
#ifdef _WIN32
	_socketConnexion = new WSocket();
	_socketGame = new WSocket();
#else
	_socketConnexion = new USocket();
	_socketGame = new USocket();
#endif
}

Network::~Network(void) {
	if (_socketConnexion)
		delete (_socketConnexion);
	if (_socketGame)
		delete (_socketGame);
}

/*
** Méthodes
*/

void				Network::init(const char *ip, int portConnexion, int portGame) {
	_socketConnexion->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	_socketConnexion->_connect(ISocket::IPv4, ip, portConnexion);

	_socketGame->_socket(ISocket::IPv4, ISocket::DGRAM, ISocket::UDP);
	_socketGame->_connect(ISocket::IPv4, ip, portGame);


	add.family = ISocket::IPv4;
	add.ip = ip;
	add.port = (unsigned short)portGame;

	std::cout << "connext ok" << std::endl;
	_game = new Game();
	if (_game->init() == false)
		throw std::runtime_error("Failed to launch Game");
}

void				Network::setClient(void) {
_socketConnexion->_FD_ZERO("rw");
	if (_game->getStart() == false)
	{
		_socketConnexion->_FD_SET("r");
		if (_game->haveOutput()) {
		//	std::cout << "FD SET Write (Connexion)" << std::endl;
			_socketConnexion->_FD_SET("w");
		}
	}
	else
	{
		_socketConnexion->_FD_SET(_socketGame, "r");
		if (_game->haveOutput()) {
			//std::cout << "FD SET Write (Game)" << std::endl;
			_socketConnexion->_FD_SET(_socketGame, "w");
		}
	}
}

bool				Network::readServerTCP(void) {
	char * header = NULL;
	char * body = NULL;
	try {
		if (_game->getState() < POSITION_PACKET_SET)
		{
			std::cout << "try to read header..." << std::endl;
			header = _socketConnexion->_recv(_proto._getSizePacketHeader(), 0);
			if (header == NULL)
				throw std::runtime_error("Fail to read(TCP) header packet");
			_proto._setNewPacketHeader(header);
			if (_proto._getHeaderSize() != 0) {
				std::cout << "try to read body of size " << _proto._getHeaderSize() << std::endl;
				body = _socketConnexion->_recv(_proto._getHeaderSize(), 0);
				if (body == NULL)
					throw std::runtime_error("Fail to read(TCP) body packet");
			}
			std::cout << "Packet correctly read" << std::endl;
		}

		const char * packet = _proto._linkPacketHeaderBody(header, body);
		_game->addInput(packet);
	}
	catch (const std::runtime_error & e) {
		std::cerr << "[Read Server]" << e.what() << std::endl;
	}
	return true;
}

bool				Network::readServerUDP(void)
{
	try {
		ISocket::tSocketAdress tmp;
		char * header = NULL;
		char * body = NULL;
		header = _socketGame->_recvfrom((unsigned int)_proto._getSizePacketHeader(), 0, &tmp);
		if (header == NULL)
			throw std::runtime_error("Fail to read(UDP) header packet");
		_proto._setNewPacketHeader(header);
		body = _socketGame->_recvfrom((unsigned int)_proto._getHeaderSize(), 0, &tmp);
		if (body == NULL)
			throw std::runtime_error("Fail to read(UDP) body packet");

		const char * packet = _proto._linkPacketHeaderBody(header, body);
		_game->addInput(packet);
	}
	catch (const std::runtime_error & e) {
		std::cerr << "[Read Server]" << e.what() << std::endl;
	}
	return true;
}

void				Network::writeServerTCP(void) {

	std::vector<const char *> listOutput = _game->getOutput();
	if (listOutput.size() > 0)
		std::cout << "[Network::writeServerTCP] : Write server TCP (" << listOutput.size() << " packets)" << std::endl;
	for (unsigned int i = 0; i < listOutput.size(); i++)
		_socketConnexion->_send(listOutput[i], _proto._getSizePacket(listOutput[i]), 0);
	return;
}

void				Network::writeServerUDP(void) {
	if (_game->getStart() == true)
	{
		std::vector<const char *> listOutput = _game->getOutput();
		//if (listOutput.size() > 0)
		//	std::cout << "[Network::writeServrUDP] : Write server UDP (" << listOutput.size() << " packets)" << std::endl;
		for (unsigned int i = 0; i < listOutput.size(); i++)
			_socketGame->_sendto(listOutput[i], _proto._getSizePacket(listOutput[i]), 0, &add);

	}
	return;
}

void				Network::run(void) {
	while (true) {
		setClient();
		int tmp = (int)(1.0 / 30.0 * 1000.0);
		/*std::cout << "Select (Timeout : " << tmp << " ms) ";
		if (_game->getStart() == false)
			std::cout << " Game not OK" << std::endl;
		else
			std::cout << " Game launched" << std::endl;*/
		_socketConnexion->_select(0, tmp);
		if (_socketConnexion->_FD_ISSET('w') == true)
			writeServerTCP();
		if (_socketConnexion->_FD_ISSET('r') == true)
			readServerTCP();
		if (_socketConnexion->_FD_ISSET(_socketGame, 'w'))
			writeServerUDP();
		if (_socketConnexion->_FD_ISSET(_socketGame, 'r'))
			readServerUDP();
	}
}
