//
// WSocket.hpp for WSocket.hpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:36:20 2015 Florent BEAURAIN
// Last update Mon Oct 26 15:36:22 2015 Florent BEAURAIN
//

#ifndef								__WSOCKET_HPP__
# define							__WSOCKET_HPP__

# define							_WINSOCK_DEPRECATED_NO_WARNINGS
# define							_CRT_SECURE_NO_WARNINGS
# define							SEND_COUNT 10

# include							<string.h>
# include							<WinSock2.h>
# include							<Windows.h>
# include							<winsock.h>
# include							<WS2tcpip.h>
# include							<stdio.h>
# include							<exception>
# include							<iostream>
# include							<stdexcept>
# include							"ISocket.hpp"

# pragma comment(lib, "ws2_32.lib")

class								WSocket : public ISocket {
public:
	WSocket(const SOCKET fd = INVALID_SOCKET);
	virtual ~WSocket(void);

	virtual void				_socket(const eSocketFamily family, const eSocketType type, const eProtocol protocol);
	virtual void				_connect(const eSocketFamily family, const char * const ip, const unsigned short port) const;
	virtual void				_connect(const eSocketFamily family, const std::string &ip, const unsigned short port) const;
	virtual ISocket			*_accept(void);
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
	virtual void				_sendto(const char * const msg, const int size, const int flags, const tSocketAdress * const adress) const;
	virtual void				_sendto(const char * const msg, const int flags, const tSocketAdress * const adress) const;
	virtual void				_sendto(const std::string &msg, const int size, const int flags, const tSocketAdress * const adress) const;
	virtual void				_sendto(const std::string &msg, const int flags, const tSocketAdress * const adress) const;

	SOCKET							getfd(void) const;

private:
	WORD								_wVersionRequested;
	WSADATA							_wsaData;
	WSABUF							_DataBuf;
	WSAOVERLAPPED				_SendOverlapped;
	WSAOVERLAPPED				_RecvOverlapped;
	SOCKET							_fd;
	fd_set							_readfds;
	fd_set							_writefds;

	char 								*_strerror(void) const;
};

#endif								/* !__WSOCKET_HPP__ */
