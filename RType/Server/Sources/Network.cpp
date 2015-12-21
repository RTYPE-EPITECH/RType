#include			"Network.hpp"
#include			<iostream>
#include			"Tools.hpp"
#include			"Client.hpp"
#include			"Game.hpp"

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
}

void				Network::deleteClient(unsigned int i) {
	std::cout << CYAN << HIGHLIGHT << "Client disconnect" << std::endl;
	_games[findGame(_clients[i])]->removeClient(_clients[i]);
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

/* Initialisation des sockets */
	_socketConnexion->_socket(ISocket::IPv4, ISocket::STREAM, ISocket::TCP);
	_socketConnexion->_bind(ISocket::IPv4, Tools::charToNumber<unsigned short>(portConnexion));
	_socketConnexion->_listen(2147483647);

	_socketGame->_socket(ISocket::IPv4, ISocket::DGRAM, ISocket::UDP);

/* Ajout de l'entré standard et de _socketGame dans _clients */
	Client		*clientEntreStandard = new Client();
	Client		*clientSocketGame = new Client();

	clientSocketGame->setSocket(_socketGame);
	clientEntreStandard->setSocket(entreStandard);
	_clients.push_back(clientSocketGame);
	_clients.push_back(clientEntreStandard);

	std::cout << "Welcome on the RType Server (Connexion port : " << portConnexion.c_str() << ")" << std::endl;
}

void				Network::setClient(void) {
	_socketConnexion->_FD_ZERO("rw");
	_socketConnexion->_FD_SET("r");
	for (unsigned int i = 0; i < _clients.size(); i++) {
		std::cout << "FD SET CLIENT " << i << std::endl;
		_socketConnexion->_FD_SET(_clients[i]->getSocket(), "r");
		if (_clients[i]->getOutput() != NULL)
			_socketConnexion->_FD_SET(_clients[i]->getSocket(), "w");
	}
}

bool				Network::readClient(unsigned int i) {
(void)i;
	try {
		//_listClient[i]->_receive();
	}
	catch (const std::exception) {
		deleteClient(i);
	}
	return true;
}

void				Network::writeClient(unsigned int i) {
(void)i;
	//_listClient[i]->_send();
	return;
}

void				Network::createGame(Client * e)
{
	Game * g = new Game(*_i);
	g->init(_init);
	e->init(g);
	_handle.init(g);
	g->addClient(e);
	_games.push_back(g);
}

void				Network::run(void)
{
	while (true) {
		std::cout << "Set client ..." << std::endl;
		setClient();
		std::cout << "Select ..." << std::endl;
		_socketConnexion->_select(60, 0);

		// Nouveau Client
		if (_socketConnexion->_FD_ISSET('r') == true) {
			newClient();
			std::cout << "New Client" << std::endl;
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
