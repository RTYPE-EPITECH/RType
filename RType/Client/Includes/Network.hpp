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

# include					"Game.hpp"

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


class						Network {
public:
	Network(void);
	~Network(void);

	void					run(void);
	void					init(const char *, int);

private:
	ISocket					*_socket;
	Game					*_game;
	Protocole				_proto;
	
	void					setClient(void);
	bool					readServer(void);
	void					writeServer(void);
};

#endif                 /* !__NETWORK_HPP__ */
