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

	virtual void				_socket(const int socket_family, const int socket_type) = 0;
	virtual ISocket			*_accept(void) = 0;
	virtual void				_bind(const int socket_family, const int port) const = 0;
	virtual void				_listen(const int backlog) const = 0;
	virtual void				_select(const int sec, const int usec) = 0;
	virtual void				_FD_ZERO(const std::string &mode) = 0;
	virtual void				_FD_SET(const std::string &mode) = 0;
	virtual void				_FD_SET(const ISocket * const, const std::string &mode) = 0;
	virtual bool				_FD_ISSET(const char mode) const = 0;
	virtual bool				_FD_ISSET(const ISocket * const, const char mode) const = 0;
	virtual void				_close(void) const = 0;
	virtual char				*_recv(const int) const = 0;
	virtual char				*_recv(const size_t, const int) const = 0;
	virtual void				_send(const char * const, const int) const = 0;
	virtual void				_send(const char * const, const size_t, const int) const = 0;
	virtual void				_send(const std::string &, const int) const = 0;
	virtual void				_send(const std::string &, const size_t, const int) const = 0;

	virtual int					getfd(void) const = 0;
};

#endif							/* !__ISOCKET_HPP__ */
