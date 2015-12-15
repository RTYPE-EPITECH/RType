//
// USocket.hpp for USocket.hpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:36:20 2015 Florent BEAURAIN
// Last update Tue Dec  1 15:25:29 2015 Florent BEAURAIN
//

#ifndef							__USOCKET_HPP__
# define							__USOCKET_HPP__

# include						<sys/socket.h>
# include						<sys/types.h>
# include						<netinet/in.h>
# include						<arpa/inet.h>
# include						<netdb.h>
# include						<unistd.h>
# include						<cstdlib>
# include						<cerrno>
# include						<cstring>
# include						<exception>
# include						<iostream>
# include						<stdexcept>
# include						"ISocket.hpp"

class								USocket : public ISocket {
public:
	USocket(const int fd = -1);
	virtual ~USocket(void);

	virtual void				_socket(const eSocketFamily family, const eSocketType type, const eProtocol protocol);
	virtual void				_connect(const eSocketFamily family, const char * const ip, const unsigned short port) const;
	virtual void				_connect(const eSocketFamily family, const std::string &ip, const unsigned short port) const;
	virtual USocket			*_accept(void);
	virtual void				_bind(const eSocketFamily family, const unsigned short port) const;
	virtual void				_listen(const int backlog) const;
	virtual void				_select(const int sec, const int usec);
	virtual void				_FD_ZERO(const std::string &mode);
	virtual void				_FD_SET(const std::string &mode);
	virtual void				_FD_SET(const ISocket * const socket, const std::string &mode);
	virtual bool				_FD_ISSET(const char mode) const;
	virtual bool				_FD_ISSET(const ISocket * const socket, const char mode) const;
	virtual void				_close(void) const;
	virtual char				*_recv(const int flags) const;
	virtual char				*_recv(const int size, const int flags) const;
	virtual char				*_recvfrom(const int flags, tSocketAdress *adress) const;
	virtual char				*_recvfrom(const int size, const int flags, tSocketAdress *adress) const;
	virtual void				_send(const char * const msg, const int flags) const;
	virtual void				_send(const char * const msg, const int size, const int flags) const;
	virtual void				_send(const std::string &msg, const int flags) const;
	virtual void				_send(const std::string &msg, const int size, const int flags) const;
	virtual void				_sendto(const char * const msg, const int flags, const tSocketAdress * const adress) const;
	virtual void				_sendto(const char * const msg, const int size, const int flags, const tSocketAdress * const adress) const;
	virtual void				_sendto(const std::string &msg, const int flags, const tSocketAdress * const adress) const;
	virtual void				_sendto(const std::string &msg, const int size, const int flags, const tSocketAdress * const adress) const;

	virtual int					getfd(void) const;

private:
	int						_fd;
	int						_fd_max;
	fd_set					_readfds;
	fd_set					_writefds;
};

#endif					/* !__USOCKET_HPP__ */
