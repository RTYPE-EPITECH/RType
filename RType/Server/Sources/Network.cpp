#include			"Network.hpp"
#include			<iostream>
#include			"Tools.hpp"
#include			"Client.hpp"
#include			"Game.hpp"
#include			"ISocket.hpp"
#include			"Player.hpp"
#ifdef _WIN32
# include			"WConditionVariable.hpp"
#else
# include			"UConditionVariable.hpp"
#endif

/*
** Constructeurs & Destructeurs
*/

Network::Network(void) {
	_socketGame = NULL;
	_socketConnexion = NULL;
	_init.push_back("WeakMonster");
}

Network::~Network(void) {
	if (_socketGame != NULL)
		delete _socketGame;
	if (_socketConnexion != NULL)
		delete _socketConnexion;
}

/*
** Méthodes
*/

void				Network::newClient(void) {
	std::cout <<  BLUE << "A new client try to connect to the server..." << WHITE << std::endl;
	Client * newClient = new Client();
	newClient->setSocket(_socketConnexion->_accept());

	// Trouver une game pour lui
	bool check = true;
	std::cout << "There are " << _games.size() << std::endl;
	for (size_t i = 0; i < _games.size() && check; i++)
	{
		std::cout << YELLOW << "The game " << i << " have " << _games[i]->getSizeAvailable() << " available" << WHITE << std::endl;
		if (_games[i]->getSizeAvailable() > 0)
		{
			newClient->init(_games[i]);
			_games[i]->addClient(newClient);
			check = false;
			std::cout << YELLOW  << "Client added to this game" << WHITE <<  std::endl;
		}
	}
	// Si aucune game OK : CReate a game
	if (check) {
		std::cout << YELLOW << "No game available : Create a new game ! " << WHITE << std::endl;
		createGame(newClient);
	}
	_clients.push_back(newClient);
}

void				Network::deleteClient(unsigned int i) {
	std::cout << CYAN << "Client disconnect" << WHITE << std::endl;
	_games[findGame(_clients[i])]->removeClient(_clients[i]);
	_clients.erase(_clients.begin() + i);
}

size_t				Network::findGame(Client *c)
{
	for (size_t i = 0; i < _games.size(); i++)
		if (_games[i]->getIdThread() == c->getIdThreadGame())
			return i;
	throw std::runtime_error("[Network] Cannot find game");
	return 0;
}

void				Network::init(const std::string & portConnexion, const std::string &portGame) {

/* Création des sockets en fonction de l'OS */
#ifdef _WIN32
	//WSocket *entreStandard = new WSocket(0);
	_socketConnexion = new WSocket();
	_socketGame = new WSocket();
	_i = new WConditionVariable();
#else
	//USocket *entreStandard = new USocket(0);
	_socketConnexion = new USocket();
	_socketGame = new USocket();
	_i = new UConditionVariable();
#endif

	_i->init();
/* Initialisation des sockets */
	_socketConnexion->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	_socketConnexion->_bind(ISocket::IPv4, Tools::charToNumber<unsigned short>(portConnexion));
	_socketConnexion->_listen(2147483647);

	_socketGame->_socket(ISocket::IPv4, ISocket::DGRAM, ISocket::UDP);
	_socketGame->_bind(ISocket::IPv4, Tools::charToNumber<unsigned short>(portGame));

/* Ajout de l'entré standard et de _socketGame dans _clients */
	//Client		*clientEntreStandard = new Client();
	Client		*clientSocketGame = new Client();

	//	clientEntreStandard->init(NULL);
	clientSocketGame->init(NULL);
	clientSocketGame->setSocket(_socketGame);
	//clientEntreStandard->setSocket(entreStandard);
	_clients.push_back(clientSocketGame);
	//_clients.push_back(clientEntreStandard);

	std::cout << GREEN << "Welcome on the RType Server (Connexion port : " << portConnexion.c_str() << ")" << WHITE << std::endl;
}

bool				Network::haveClientsUDPOutput() const
{
	bool check = false;
	for (size_t j = 1; j < _clients.size(); j++)
		if (_clients[j]->getState() == POSITION_PACKET_SET)
			if (_clients[j]->haveOutput() && _clients[j]->isUDPset)
			{
				std::cout << "OK THEN SOMETHING TO WRITE IN UDP" << std::endl;
				check = true;
				break;
			}
	return check;
}

void				Network::setClient(void) {
	_socketConnexion->_FD_ZERO("rw");
	_socketConnexion->_FD_SET("r");
	//std::cout << "There are " << _clients.size() << " clients (Server included)" << std::endl;
	for (unsigned int i = 0; i < _clients.size(); i++) {
		if (_clients[i]->getState() < POSITION_PACKET_SET)
		{
			//if (i > 0)
				//std::cout << "Client " << i << " is trying to connect" << std::endl;
			_socketConnexion->_FD_SET(_clients[i]->getSocket(), "r");
			if (_clients[i]->haveOutput()) {
				std::cout << "There are severals output" << std::endl;
				_socketConnexion->_FD_SET(_clients[i]->getSocket(), "w");
			}
		}
	}
	_socketConnexion->_FD_SET(_socketGame, "r");
	if (haveClientsUDPOutput())
		_socketConnexion->_FD_SET(_socketGame, "w");
}

bool				Network::readClientTCP(unsigned int i) {
	char * header = NULL;
	char * body = NULL;
	try {
		if (_clients[i]->getState() < POSITION_PACKET_SET)
		{
			std::cout << "try to read TCP header..." << i << std::endl;
			header = _clients[i]->getSocket()->_recv(_proto._getSizePacketHeader(), 0);
			if (header == NULL)
				throw std::runtime_error("Fail to read(TCP) body packet");
			_proto._setNewPacketHeader(header);
			if (_proto._getHeaderSize() != 0) {
				std::cout << "try to read TCP body of size " << _proto._getHeaderSize() << std::endl;
				body = _clients[i]->getSocket()->_recv(_proto._getHeaderSize(), 0);
				if (body == NULL)
					throw std::runtime_error("Fail to read(TCP) body packet");
			}
			std::cout << "Packet correctly TCP read" << std::endl;
			const char * packet = _proto._linkPacketHeaderBody(header, body);
			_clients[i]->addInput(packet);
		}
		// packet TCP during the game : ignored
	}
	catch (const std::runtime_error & e) {
		deleteClient(i);
		std::cerr << "[Read Client TCP " << i << "]" << e.what() << std::endl;
	}
	return true;
}

bool				Network::readClientUDP()
{
	try {
		char * header = NULL, * body = NULL;
		ISocket::tSocketAdress add;
		std::cout << "Read UDP" << std::endl;
		header = _socketGame->_recvfrom((unsigned int)_proto._getSizePacketHeader(), 0, &add);
		if (header == NULL)
			throw std::runtime_error("Fail to read(UDP) header packet");
		_proto._setNewPacketHeader(header);
		if (_proto._getHeaderSize() > 0)
		{
			body = _socketGame->_recvfrom((unsigned int)_proto._getHeaderSize(), 0, &add);
			if (body == NULL)
				throw std::runtime_error("Fail to read(UDP) body packet");
		}
		short id = _proto._getHeaderId();
		int i = -1;
		for (size_t j = 1; j < _clients.size(); j++) {
			if (_clients[j]->getPlayer()->getId() == (size_t)id)
			{
				i = (int)j;
				break;
			}
		}
		if (i != -1)
		{
			_clients[i]->_adr.ip = add.ip;
			_clients[i]->_adr.port = add.port;
			_clients[i]->_adr.family = add.family;
			if (_clients[i]->getState() < POSITION_PACKET_SET)
				throw std::runtime_error("connexion not finished yet");
			_clients[i]->isUDPset = true;
			const char * packet = _proto._linkPacketHeaderBody(header, body);
			_clients[i]->addInput(packet);
		}
		else
			throw std::runtime_error(std::string("Unknow Client " + Tools::NumberToString(id)));
	}
	catch (const std::runtime_error & e) {
		std::cerr << "[Read Client UDP ]" << e.what() << std::endl;
	}
	return true;
}

void				Network::writeClientTCP(unsigned int i) {
	try {
		std::vector<const char *> _toSend = _clients[i]->getAllOutput();
		if (_clients[i]->getState() < POSITION_PACKET_SET)
		{
			for (size_t j = 0; j < _toSend.size(); j++) {
				_clients[i]->getSocket()->_send(_toSend[j], _proto._getSizePacket(_toSend[j]), 0);
			}
		}
		// packet TCP to send during Game, ignored
		else
		{
			// do nothing
		}
	}
	catch (const std::exception) {
		std::cerr << RED << "Failed to write client (disconnect)" << WHITE << std::endl;
		deleteClient(i);
	}
	return;
}

void				Network::writeClientUDP()
{
	std::vector<const char *> _toSend;
	for (size_t j = 1; j < _clients.size(); j++)
	{
		if (!_clients[j]->isUDPset && j != 0)
			std::cout << "Try to write to a client which is not ready for UDP" << std::endl;
		if (!_clients[j]->haveOutput() && j != 0)
			std::cout << "NOTHING TO SEND" << std::endl;
		if (_clients[j]->haveOutput() && _clients[j]->getState() == POSITION_PACKET_SET && _clients[j]->isUDPset)
		{
			_toSend = _clients[j]->getAllOutput();
			for (size_t i = 0; i < _toSend.size(); i++)
			{
				_proto._setNewPacket(_toSend[i]);
				std::cout << "Envoie Packet UDP : OpCode : " << (int)_proto._getHeaderOpcode() << std::endl;
				if (_proto._getHeaderOpcode() == 4)
				{
					std::cout << "There are : " << (int)_proto._getArrayPositionLenght() << std::endl;
				}
				_socketGame->_sendto(_toSend[i],
					_proto._getSizePacket(_toSend[i]),
					0,
					&(_clients[j]->_adr));
			}
		}
	}

}

void				Network::createGame(Client * e)
{
	Game * g = new Game(_i);
	g->init(_init);
	if (g->addClient(e))
	{
		_handle.init(g);
		std::cout << BLUE << "Client added" << WHITE <<  std::endl;
		_games.push_back(g);
	}
	else
		std::cout << RED << "Client not added !" << WHITE << std::endl;
}

void				Network::run(void)
{
	while (true) {
		//std::cout << "Set client ..." << std::endl;
		setClient();
		//std::cout << YELLOW << "Select ... (Timeout : 5s)" << WHITE << std::endl;
		int tmp = (int)(1.0 / 30.0 * 1000.0);
		_socketConnexion->_select(0, tmp);
		//std::cout << YELLOW << "... Select over " << WHITE << std::endl;
		_i->sendSignal();
		if (_socketConnexion->_FD_ISSET('r') == true) {
			newClient();
		}
		else {
				if (_socketConnexion->_FD_ISSET(_socketGame, 'r') == true)
					readClientUDP();
				if (_socketConnexion->_FD_ISSET(_socketGame, 'w') == true) {
					std::cout << "Can write UDP" << std::endl;
					writeClientUDP();
				}
				for (unsigned int i = 1; i < _clients.size(); i++) {
					if (_socketConnexion->_FD_ISSET(_clients[i]->getSocket(), 'w') == true)
						writeClientTCP(i);
					if (_socketConnexion->_FD_ISSET(_clients[i]->getSocket(), 'r') == true)
						if (readClientTCP(i) == false)
							return;
				}
			}
	}
}
