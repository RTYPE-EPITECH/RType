//
// USocket.cpp for USocket.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:44:59 2015 Florent BEAURAIN
// Last update Mon Nov  2 13:04:11 2015 Florent BEAURAIN
//

#include		"WSocket.hpp"

/*
** Constructeurs & Destructeurs
*/

WSocket::WSocket(const SOCKET fd) {
	_fd = fd;
	_fd_max = fd;
	_FD_ZERO("rw");
	this->wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(this->wVersionRequested, &(this->wsaData)) != 0)
		throw std::runtime_error("WSAStartup failed");
	if (LOBYTE(this->wsaData.wVersion) != 2 || HIBYTE(this->wsaData.wVersion) != 2) {
		throw std::runtime_error("Could not find a usable version of Winsock.dll");
		WSACleanup();
	}
	std::cout << "The Winsock 2.2 dll was found okay" << std::endl;
}

WSocket::~WSocket(void) {
	_close();
	WSACleanup();
}

/*
** Getters
*/

SOCKET					WSocket::getfd(void) const {
	return (int)_fd;
}

/*
** Méthodes
*/

void					WSocket::_socket(const int socketType) {
	if ((this->_fd = WSASocketW(AF_INET, socketType, IPPROTO_UDP, NULL, 0, 0)) == INVALID_SOCKET)
		throw std::runtime_error("WSASocket function failed");
	_fd_max = _fd;
	_FD_ZERO("rw");

	return;
}

void					WSocket::_connect(const char * const ip, const int port) const {
	sockaddr_in			service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(port);
	if (WSAConnect(_fd, (SOCKADDR *)&(service), sizeof(service), 0, 0, 0, 0) == SOCKET_ERROR) {
		throw std::runtime_error(strerror(errno));
		WSACleanup();
	}
	return;
}

void					WSocket::_connect(const std::string &ip, const int port) const {
	sockaddr_in			service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip.c_str());
	service.sin_port = htons(port);
	if (WSAConnect(_fd, (SOCKADDR *)&(service), sizeof(service), 0, 0, 0, 0) == SOCKET_ERROR) {
		throw std::runtime_error(strerror(errno));
		WSACleanup();
	}
	return;

}

ISocket				*WSocket::_accept(void) {
	SOCKET			fd;
	sockaddr_in		saClient;
	int				iClientSize = sizeof(saClient);
	if ((fd = WSAAccept(this->_fd, (SOCKADDR *)&saClient, &iClientSize, NULL, NULL)) == SOCKET_ERROR)
		throw std::runtime_error("WSAAccept function failed");
	if (_fd_max < fd)
		_fd_max = fd;

	WSocket	*newConnection = new WSocket(fd);
	return newConnection;
}

void					WSocket::_bind(const int port) const {
	sockaddr_in			service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = htons(INADDR_ANY);
	service.sin_port = htons(port);
	if (bind(this->_fd, (SOCKADDR *)&(service), sizeof(service)) == SOCKET_ERROR) {
		throw std::runtime_error("bind funtion failed");
		_close();
		WSACleanup();
	}

	return;
}

void					WSocket::_listen(const int backlog) const {
	if (listen(this->_fd, backlog) == SOCKET_ERROR)
		throw std::runtime_error("listen function failed");

	return;
}

void					WSocket::_select(const int sec, const int usec) {
	struct timeval	tv;

  	tv.tv_sec = sec;
  	tv.tv_usec = usec;
	if (select(_fd_max + 1, &_readfds, &_writefds, NULL, &tv) == SOCKET_ERROR) {
		throw std::runtime_error("Select function failed");
	}

	return;
}

void					WSocket::_FD_ZERO(const std::string &mode) {
	if (mode == "r")
		FD_ZERO(&_readfds);
	else if (mode == "w")
		FD_ZERO(&_writefds);
	else if (mode == "rw") {
		FD_ZERO(&_readfds);
		FD_ZERO(&_writefds);
	}
	else
		std::runtime_error("[Error]: bad mode for _FD_ZERO()");

	return;
}

void					WSocket::_FD_SET(const std::string &mode) {
	if (mode == "r")
		FD_SET(_fd, &_readfds);
	else if (mode == "w")
		FD_SET(_fd, &_writefds);
	else if (mode == "rw") {
		FD_SET(_fd, &_readfds);
		FD_SET(_fd, &_writefds);
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_SET()");

	return;
}

void					WSocket::_FD_SET(const ISocket * const socket, const std::string &mode) {
	if (mode == "r")
		FD_SET(((WSocket *)socket)->getfd(), &_readfds);
	else if (mode == "w")
		FD_SET(((WSocket *)socket)->getfd(), &_writefds);
	else if (mode == "rw") {
		FD_SET(((WSocket *)socket)->getfd(), &_readfds);
		FD_SET(((WSocket *)socket)->getfd(), &_writefds);
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_SET()");

	return;
}

bool					WSocket::_FD_ISSET(const char mode) const {
	if (mode == 'r') {
		if (FD_ISSET(_fd, &_readfds))
			return true;
		}
	else if (mode == 'w') {
		if (FD_ISSET(_fd, &_writefds))
			return true;
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_ISSET()");

	return false;
}

bool					WSocket::_FD_ISSET(const ISocket * const socket, const char mode) const {
	if (mode == 'r') {
		if (FD_ISSET(((WSocket *)socket)->getfd(), &_readfds))
			return true;
	}
	else if (mode == 'w') {
		if (FD_ISSET(((WSocket *)socket)->getfd(), &_writefds))
			return true;
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_ISSET()");

	return false;
}

void					WSocket::_close(void) const {
	if (closesocket(_fd) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

char					*WSocket::_recv(const int flags) const {
	char				*msg = new char[30721];
	size_t				ret;

	if ((ret = recv(_fd, msg, 30720, flags)) <= 0)
		throw std::runtime_error(strerror(errno));
	msg[ret] = '\0';

	return msg;
}

char					*WSocket::_recv(const size_t size, const int flags) const {
	char				*msg = new char[size + 1];
	size_t			ret;

	if ((ret = recv(_fd, msg, size, flags)) <= 0)
		throw std::runtime_error(strerror(errno));
	msg[ret] = '\0';

	return msg;
}

char					*WSocket::_recvFrom(const size_t size, const int flags) const {
	char				*msg = new char[size + 1];
	sockaddr			*structsend;
	int len = sizeof(structsend);
	size_t				ret;

	if ((ret = recvfrom(_fd, msg, size, flags, (SOCKADDR *)structsend, &len)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));
	msg[ret] = '\0';

	return msg;
}

void					WSocket::_send(const char * const msg, const int flags) const {
	size_t			ret;

	if ((ret = send(_fd, msg, strlen(msg), flags)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_send(const char * const msg, const size_t size, const int flags) const {
	size_t			ret;

	if ((ret = send(_fd, msg, size, flags)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_send(const std::string &msg, const int flags) const {
	size_t			ret;

	if ((ret = send(_fd, msg.c_str(), msg.size(), flags)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_send(const std::string &msg, const size_t size, const int flags) const {
	size_t			ret;

	if ((ret = send(_fd, msg.c_str(), size, flags)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_sendto(const std::string &msg, const size_t size, const int flags) const {
	sockaddr_in		*recvStruct;
	int len = sizeof(recvStruct);
	size_t			ret;

	if ((ret = sendto(_fd, msg.c_str(), size, flags, (SOCKADDR *)recvStruct, len)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_sendto(const std::string &msg, const int flags) const {
	sockaddr_in		*recvStruct;
	int len = sizeof(recvStruct);
	size_t			ret;

	if ((ret = sendto(_fd, msg.c_str(), strlen(msg.c_str()), flags, (SOCKADDR *)recvStruct, len)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_sendto(const char *msg, const size_t size, const int flags) const {
	sockaddr_in		*recvStruct;
	int len = sizeof(recvStruct);
	size_t			ret;

	if ((ret = sendto(_fd, msg, size, flags, (SOCKADDR *)recvStruct, len)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}

void					WSocket::_sendto(const char *msg, const int flags) const {
	sockaddr		*recvStruct;
	int len = sizeof(recvStruct);
	size_t			ret;

	if ((ret = sendto(_fd, msg, strlen(msg), flags, (SOCKADDR *)recvStruct, len)) == SOCKET_ERROR)
		throw std::runtime_error(strerror(errno));

	return;
}