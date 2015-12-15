#ifndef                 __NETWORK_HPP__
# define                __NETWORK_HPP__

# include					<exception>
# include					<iostream>
# include					<vector>
# include					<algorithm>
#ifdef _WIN32
# include					"WSocket.hpp"
#else
# include					"USocket.hpp"
#endif // WIN32
# include					"IConditionVariable.hpp"
# include					"Protocole.hpp"
# include					"HandleThread.hpp"
# define		RED			"\x1B[31m"
# define		GREEN		"\033[32m"
# define		YELLOW		"\033[33m"
# define		BLUE		"\033[34m"
# define		PURPLE		"\033[35m"
# define		WHITE		"\x1B[0m"
# define		CYAN		"\x1B[36m"
# define		HIGHLIGHT	"\033[1m"
# define		DEFAULT		"\033[0m"
# define		BLINK		"\033[5m"
# define		UNDERLINE	"\033[4m"

class Client;
class Game;

class						Network {
public:
	Network(void);
	~Network(void);

	void					run(void);
	void					init(const std::string &);

private:
	ISocket					*_socket;
	IConditionVariable		*_i;
	Protocole				_proto;
	HandleThread			_handle;
	std::vector<Game *>		_games;
	std::vector<Client *>	_clients;

	std::vector<std::string> _init;

	void					newClient(void);
	void					deleteClient(unsigned int);
	void					setClient(void);
	bool					readClient(unsigned int);
	void					writeClient(unsigned int);

	void					createGame(Client *);
	size_t					findGame(Client *);
};

#endif                 /* !__NETWORK_HPP__ */
