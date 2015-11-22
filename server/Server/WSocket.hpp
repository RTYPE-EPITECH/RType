//
// WSocket.hpp for WSocket.hpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:36:20 2015 Florent BEAURAIN
// Last update Mon Oct 26 15:36:22 2015 Florent BEAURAIN
//

#ifndef							__WSOCKET_HPP__
# define						__WSOCKET_HPP__

# include						<sys/types.h>
# include						<cstdlib>
# include						<cerrno>
# include						<cstring>
# include						<exception>
# include						<iostream>
# include						<stdexcept>
# include						"ISocket.hpp"

class								WSocket : public ISocket {
public:
	WSocket(const int fd = -1);
	virtual ~WSocket(void);

	virtual void				_socket(const int socketType);
	virtual void				_connect(const char * const ip, const int port) const;
	virtual void				_connect(const std::string &ip, const int port) const;
	virtual WSocket			*_accept(void);
	virtual void				_bind(const int port) const;
	virtual void				_listen(const int backlog) const;
	virtual void				_select(const int sec, const int usec);
	virtual void				_FD_ZERO(const std::string &mode);
	virtual void				_FD_SET(const std::string &mode);
	virtual void				_FD_SET(const ISocket * const socket, const std::string &mode);
	virtual bool				_FD_ISSET(const char mode) const;
	virtual bool				_FD_ISSET(const ISocket * const socket, const char mode) const;
	virtual void				_close(void) const;
	virtual char				*_recv(const int flags) const;
	virtual char				*_recv(const size_t size, const int flags) const;
	virtual void				_send(const char * const msg, const int flags) const;
	virtual void				_send(const char * const msg, const size_t size, const int flags) const;
	virtual void				_send(const std::string &msg, const int flags) const;
	virtual void				_send(const std::string &msg, const size_t size, const int flags) const;

	virtual int					getfd(void) const;

private:
	int						_fd;
	int						_fd_max;
	fd_set					_readfds;
	fd_set					_writefds;
};

#endif					/* !__WSOCKET_HPP__ */
