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
	_FD_ZERO("rw");
	_wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(_wVersionRequested, &(_wsaData)) != 0)
		throw std::runtime_error(_strerror());
	if (LOBYTE(_wsaData.wVersion) != 2 || HIBYTE(_wsaData.wVersion) != 2)
		throw std::runtime_error(_strerror());
}

WSocket::~WSocket(void) {
	_close();
	WSACleanup();
}

/*
** Getters
*/

SOCKET					WSocket::getfd(void) const {
	return _fd;
}

/*
** Méthodes
*/

char					*WSocket::_strerror(void) const {
	char	*error = NULL;

	if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPTSTR>(&error), 0, NULL) == 0)
		throw std::runtime_error("[Error]: FormatMessage() failed");

	return error;
}

void					WSocket::_socket(const eSocketFamily family, const eSocketType type, const eProtocol protocol) {
	if ((_fd = WSASocketW(family, type, protocol, NULL, 0, 0)) == INVALID_SOCKET)
		throw std::runtime_error(_strerror());
	_FD_ZERO("rw");
}

void					WSocket::_connect(const eSocketFamily family, const char * const ip, const unsigned short port) const {
	struct sockaddr_in			s_in;

	s_in.sin_family = family;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip);

	if (WSAConnect(_fd, reinterpret_cast<struct sockaddr *>(&s_in), sizeof(struct sockaddr_in), 0, 0, 0, 0) == SOCKET_ERROR) {
		std::cout << "ip : " << ip << ", port " << port << ", error : " << WSAGetLastError() << std::endl;
		throw std::runtime_error("[ERROR WSOCKET] : connect failed");
	}
}

void					WSocket::_connect(const eSocketFamily family, const std::string &ip, const unsigned short port) const {
	struct sockaddr_in			s_in;

	s_in.sin_family = family;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip.c_str());

	if (WSAConnect(_fd, reinterpret_cast<struct sockaddr *>(&s_in), sizeof(struct sockaddr_in), 0, 0, 0, 0) == SOCKET_ERROR) {
		throw std::runtime_error("[ERROR WSOCKET] : connect failed");
	}
}

ISocket				*WSocket::_accept(void) {
	SOCKET								fd;
	struct sockaddr_in		s_in;
	int										sizeS_in = sizeof(s_in);

	if ((fd = WSAAccept(_fd, reinterpret_cast<struct sockaddr *>(&s_in), &sizeS_in, NULL, NULL)) == SOCKET_ERROR)
		{
			std::cerr << WSAGetLastError() << std::endl;
			throw std::runtime_error(_strerror());
		}
	std::cout << "Accept ok" << std::endl;
	WSocket	*newConnection = new WSocket(fd);
	return newConnection;
}

void					WSocket::_bind(const eSocketFamily family, const unsigned short port) const {
	struct sockaddr_in			s_in;

	s_in.sin_family = family;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = htons(INADDR_ANY);

	if (bind(_fd, reinterpret_cast<struct sockaddr *>(&s_in), sizeof(struct sockaddr_in)) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_listen(const int backlog) const {
	if (listen(_fd, backlog) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_select(const int sec, const int usec) {
	struct timeval	tv;

  tv.tv_sec = sec;
  tv.tv_usec = usec;
  if (select(1, &_readfds, &_writefds, NULL, &tv) == SOCKET_ERROR)
  {
	  std::cout << WSAGetLastError() << std::endl;
	  throw std::runtime_error("Failed to select");
  }
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
		throw std::runtime_error("[Error]: bad mode for _FD_ZERO()");

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
		throw std::runtime_error(_strerror());
}

char					*WSocket::_recv(const int flags) const {
	char				*msg = new char[30721];
	int					ret;

	if ((ret = recv(_fd, msg, 30720, flags)) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
	//msg[ret] = '\0';

	return msg;
}

char					*WSocket::_recv(const int size, const int flags) const {
	char				*msg = new char[size + 1];
	int					ret;

	if ((ret = recv(_fd, msg, size, flags)) == SOCKET_ERROR)
	{
		std::cerr << WSAGetLastError() << std::endl;
		throw std::runtime_error(_strerror());
	}
	//msg[ret] = '\0';
	return msg;
}

char					*WSocket::_recvfrom(const int flags, tSocketAdress *adress) const {
	char									*msg = new char[30721];
	int										ret;
	struct sockaddr_in		src_addr;

	if ((ret = recvfrom(_fd, msg, 30720, flags, reinterpret_cast<struct sockaddr *>(&src_addr), reinterpret_cast<socklen_t *>(sizeof(src_addr)))) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
	msg[ret] = '\0';

	if (src_addr.sin_family == AF_INET)
		adress->family = IPv4;
	else if (src_addr.sin_family == AF_INET6)
		adress->family = IPv6;
	adress->ip = inet_ntoa(src_addr.sin_addr);
	adress->port = ntohs(src_addr.sin_port);

	return msg;
}

char					*WSocket::_recvfrom(const int size, const int flags, tSocketAdress *adress) const {
	char										*msg = new char[size + 1];
	int											ret;
	struct sockaddr_in			src_addr;

	if ((ret = recvfrom(_fd, msg, size, flags, reinterpret_cast<struct sockaddr *>(&src_addr), reinterpret_cast<socklen_t *>(sizeof(src_addr)))) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
	msg[ret] = '\0';

	if (src_addr.sin_family == AF_INET)
		adress->family = IPv4;
	else if (src_addr.sin_family == AF_INET6)
		adress->family = IPv6;
	adress->ip = inet_ntoa(src_addr.sin_addr);
	adress->port = ntohs(src_addr.sin_port);

	return msg;
}

void					WSocket::_send(const char * const msg, const int flags) const {
	if (send(_fd, msg, (int)strlen(msg), flags) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_send(const char * const msg, const int size, const int flags) const {
	if (send(_fd, msg, size, flags) == SOCKET_ERROR)
	{
		std::cerr << "[WSocket::_send] : " << WSAGetLastError() << std::endl;
		throw std::runtime_error(_strerror());
	}
}

void					WSocket::_send(const std::string &msg, const int flags) const {
	if (send(_fd, msg.c_str(), (int)msg.size(), flags) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_send(const std::string &msg, const int size, const int flags) const {
	if (send(_fd, msg.c_str(), size, flags) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_sendto(const char * const msg, const int flags, const tSocketAdress * const adress) const {
	struct sockaddr_in	dest_addr;
	struct in_addr			addr;
	struct hostent			*h;

	if ((h = gethostbyname(adress->ip.c_str())) == NULL)
		throw std::runtime_error(strerror(errno));
	memcpy(&addr, h->h_addr, sizeof(addr));
	dest_addr.sin_family = adress->family;
	dest_addr.sin_port = htons(adress->port);
	dest_addr.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

	if (sendto(_fd, msg, (int)strlen(msg), flags, reinterpret_cast<struct sockaddr *>(&dest_addr), sizeof(dest_addr)) == -SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_sendto(const char * const msg, const int size, const int flags, const tSocketAdress * const adress) const {
	struct sockaddr_in	dest_addr;
	struct in_addr			addr;
	struct hostent			*h;

	if ((h = gethostbyname(adress->ip.c_str())) == NULL)
		throw std::runtime_error(strerror(errno));
	memcpy(&addr, h->h_addr, sizeof(addr));
	dest_addr.sin_family = adress->family;
	dest_addr.sin_port = htons(adress->port);
	dest_addr.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

	if (sendto(_fd, msg, size, flags, reinterpret_cast<struct sockaddr *>(&dest_addr), sizeof(dest_addr)) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_sendto(const std::string &msg, const int flags, const tSocketAdress * const adress) const {
	struct sockaddr_in	dest_addr;
	struct in_addr			addr;
	struct hostent			*h;

	if ((h = gethostbyname(adress->ip.c_str())) == NULL)
		throw std::runtime_error(strerror(errno));
	memcpy(&addr, h->h_addr, sizeof(addr));
	dest_addr.sin_family = adress->family;
	dest_addr.sin_port = htons(adress->port);
	dest_addr.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

	if (sendto(_fd, msg.c_str(), (int)msg.size(), flags, reinterpret_cast<struct sockaddr *>(&dest_addr), sizeof(dest_addr)) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}

void					WSocket::_sendto(const std::string &msg, const int size, const int flags, const tSocketAdress * const adress) const {
	struct sockaddr_in	dest_addr;
	struct in_addr			addr;
	struct hostent			*h;

	if ((h = gethostbyname(adress->ip.c_str())) == NULL)
		throw std::runtime_error(strerror(errno));
	memcpy(&addr, h->h_addr, sizeof(addr));
	dest_addr.sin_family = adress->family;
	dest_addr.sin_port = htons(adress->port);
	dest_addr.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

	if (sendto(_fd, msg.c_str(), size, flags, reinterpret_cast<struct sockaddr *>(&dest_addr), sizeof(dest_addr)) == SOCKET_ERROR)
		throw std::runtime_error(_strerror());
}
