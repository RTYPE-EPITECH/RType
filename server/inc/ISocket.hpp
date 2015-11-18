//
// ISocket.hpp for ISocket.hh in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 14:55:10 2015 Florent BEAURAIN
// Last update Mon Oct 26 14:55:11 2015 Florent BEAURAIN
//

#ifndef							__ISOCKET_HPP__
# define						__ISOCKET_HPP__

# include						<iostream>

class							ISocket {
public:
	virtual ~ISocket(void) {}

	virtual void				_socket(int socket_family, int socket_type, int protocol) = 0;
	virtual ISocket			*_accept(void) = 0;
	virtual void				_bind(int socket_family, int port) const = 0;
	virtual void				_listen(int backlog) const = 0;
	virtual void				_select(int sec, int usec) = 0;
	virtual void				_FD_ZERO(std::string mode) = 0;
	virtual void				_FD_SET(std::string mode) = 0;
	virtual void				_FD_SET(const ISocket *, std::string mode) = 0;
	virtual bool				_FD_ISSET(char mode) const = 0;
	virtual bool				_FD_ISSET(const ISocket *, char mode) const = 0;
	virtual void				_close(void) const = 0;
	virtual char				*_recv(int) const = 0;
	virtual char				*_recv(size_t, int) const = 0;
	virtual void				_send(const char *, int) const = 0;
	virtual void				_send(const char *, size_t, int) const = 0;
	virtual void				_send(const std::string, int) const = 0;
	virtual void				_send(const std::string, size_t, int) const = 0;

	virtual int					getfd(void) const = 0;
};

#endif							/* !__ISOCKET_HPP__ */
