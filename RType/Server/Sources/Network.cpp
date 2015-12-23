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
	std::cout <<  "A new client try to connect to the server..." << std::endl;
	Client * newClient = new Client();
	newClient->setSocket(_socketConnexion->_accept());

	// Trouver une game pour lui
	bool check = true;
	for (size_t i = 0; i < _games.size() && check; i++)
		if (_games[i]->getSizeAvailable() != 0)
		{
			newClient->init(_games[i]);
			_games[i]->addClient(newClient);
			check = false;
		}
	// Si aucune game OK : CReate a game
	if (check)
		createGame(newClient);
	_clients.push_back(newClient);
}

void				Network::deleteClient(unsigned int i) {
	std::cout << CYAN << HIGHLIGHT << "Client disconnect" << std::endl;
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
	WSocket *entreStandard = new WSocket(0);
	_socketConnexion = new WSocket();
	_socketGame = new WSocket();
	_i = new WConditionVariable();
#else
	USocket *entreStandard = new USocket(0);
	_socketConnexion = new USocket();
	_socketGame = new USocket();
	entreStandard = new USocket(0);
	_i = new UConditionVariable();
#endif

	_i->init();
/* Initialisation des sockets */
	_socketConnexion->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	_socketConnexion->_bind(ISocket::IPv4, Tools::charToNumber<unsigned short>(portConnexion));
	_socketConnexion->_listen(2147483647);

	_socketGame->_socket(ISocket::IPv4, ISocket::DGRAM, ISocket::UDP);

/* Ajout de l'entré standard et de _socketGame dans _clients */
	Client		*clientEntreStandard = new Client();
	Client		*clientSocketGame = new Client();

	//	clientEntreStandard->init(NULL);
		clientSocketGame->init(NULL);
	clientSocketGame->setSocket(_socketGame);
	//clientEntreStandard->setSocket(entreStandard);
	_clients.push_back(clientSocketGame);
	//_clients.push_back(clientEntreStandard);

	std::cout << GREEN << "Welcome on the RType Server (Connexion port : " << portConnexion.c_str() << ")" << WHITE << std::endl;
}

void				Network::setClient(void) {
	_socketConnexion->_FD_ZERO("rw");
	_socketConnexion->_FD_SET("r");
	std::cout << "There are " << _clients.size() << " clients (Server included)" << std::endl;
	for (unsigned int i = 0; i < _clients.size(); i++) {
		if (_clients[i]->getState() < POSITION_PACKET_SET)
		{
			if (i > 0)
				std::cout << "Client " << i << " is trying to connect" << std::endl;
			_socketConnexion->_FD_SET(_clients[i]->getSocket(), "r");
			if (_clients[i]->haveOutput())
				_socketConnexion->_FD_SET(_clients[i]->getSocket(), "w");
		}
	}
}

bool				Network::readClient(unsigned int i) {
	char * header = NULL;
	char * body = NULL;
	try {
		std::cout << "Try to read Client " << i << std::endl;
		if (_clients[i]->getState() < POSITION_PACKET_SET)
		{
			header = _socketConnexion->_recv(_proto._getSizePacketHeader(), 0);
			if (header == NULL){
				std::cerr << RED << "Fail to read (TCP) header" << WHITE << std::endl;
				return false;
			}
			_proto._setNewPacketHeader(header);
			body = _socketConnexion->_recv(_proto._getHeaderSize(), 0);
			if (body == NULL) {
				std::cerr << RED << "Fail to read (TCP) body packet" << WHITE << std::endl;
				return false;
			}
		}
		else
		{
			ISocket::tSocketAdress add;
			header = _socketGame->_recvfrom((unsigned int)_proto._getSizePacketHeader(), 0, &add);
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
		}
		const char * packet = _proto._linkPacketHeaderBody(header, body);
		_clients[i]->addInput(packet);
	}
	catch (const std::runtime_error & e) {
		deleteClient(i);
		std::cerr << "[Read Client " << i << "]" << e.what() << std::endl;
	}
	return true;
}

void				Network::writeClient(unsigned int i) {
	try {
		std::vector<const char *> _toSend = _clients[i]->getAllOutput();
		if (_clients[i]->getState() < POSITION_PACKET_SET)
		{
			for (size_t i = 0; i < _toSend.size(); i++)
				_socketConnexion->_send(_toSend[i], _proto._getSizePacket(_toSend[i]), 0);
		}
		else
		{
			ISocket::tSocketAdress add;
			for (size_t i = 0; i < _toSend.size(); i++)
			{
				_proto._setNewPacketHeader(_toSend[i]);
				_socketGame->_sendto(_toSend[i],
					_proto._getSizePacket(_toSend[i]),
					&(_clients[i]->_adr));
			}
		}
	}
	catch (const std::exception) {
		std::cerr << RED << "Failed to write client (disconnect)" << WHITE << std::endl;
		deleteClient(i);
	}
	return;
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
		std::cout << "Set client ..." << std::endl;
		setClient();
		std::cout << YELLOW << "Select ... (Timeout : 60s)" << WHITE << std::endl;
		_socketConnexion->_select(60, 0);
		std::cout << YELLOW << "... Select over " << WHITE << std::endl;
		_i->sendSignal();
		// Nouveau Client
		if (_socketConnexion->_FD_ISSET('r') == true) {
			newClient();
		}
		else
		{
			for (unsigned int i = 0; i < _clients.size(); i++) {
				if (_socketConnexion->_FD_ISSET(_clients[i]->getSocket(), 'w') == true)
					writeClient(i);
				if (_socketConnexion->_FD_ISSET(_clients[i]->getSocket(), 'r') == true)
					if (readClient(i) == false)
						return;
			}
		}
	}
}
