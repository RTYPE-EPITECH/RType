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
# define							__ISOCKET_HPP__

# include						<iostream>

class								ISocket {
public:
	virtual ~ISocket(void) {}

	virtual void				_socket(const int socketType) = 0;
	virtual void				_connect(const char * const ip, const int port) const = 0;
	virtual void				_connect(const std::string &ip, const int port) const = 0;
	virtual ISocket				*_accept(void) = 0;
	virtual void				_bind(const int port) const = 0;
	virtual void				_listen(const int backlog) const = 0;
	virtual void				_select(const int sec, const int usec) = 0;
	virtual void				_FD_ZERO(const std::string &mode) = 0;
	virtual void				_FD_SET(const std::string &mode) = 0;
	virtual void				_FD_SET(const ISocket * const socket, const std::string &mode) = 0;
	virtual bool				_FD_ISSET(const char mode) const = 0;
	virtual bool				_FD_ISSET(const ISocket * const socket, const char mode) const = 0;
	virtual void				_close(void) const = 0;
	virtual char				*_recv(const int flags) const = 0;
	virtual char				*_recv(const size_t size, const int flags) const = 0;
	virtual void				_send(const char * const msg, const int flags) const = 0;
	virtual void				_send(const char * const msg, const size_t size, const int flags) const = 0;
	virtual void				_send(const std::string &msg, const int flags) const = 0;
	virtual void				_send(const std::string &msg, const size_t size, const int flags) const = 0;
};

#endif							/* !__ISOCKET_HPP__ */
