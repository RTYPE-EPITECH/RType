#ifndef                 __NETWORK_HPP__
# define                __NETWORK_HPP__

# include					<exception>
# include					<iostream>
# include					<vector>
# include					<algorithm>
#ifdef WIN32
# include					"WSocket.hpp"
#else
# include					"USocket.hpp"
#endif // WIN32
# include					"IConditionVariable.hpp"

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
  void					init(const std::string &);

private:
	ISocket					*_socket;
	IConditionVariable		*_i;
	void					newClient(void);
	void					deleteClient(unsigned int);
	void					setClient(void);
	bool					readClient(unsigned int);
	void					writeClient(unsigned int);
};

#endif                 /* !__NETWORK_HPP__ */
