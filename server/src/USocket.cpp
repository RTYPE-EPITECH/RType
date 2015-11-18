//
// USocket.cpp for USocket.cpp in /home/beauraF/Documents/Epitech/TEK3/CPP/cpp_spider/spider
//
// Made by Florent BEAURAIN
// Login   <beauraF@epitech.net>
//
// Started on  Mon Oct 26 15:44:59 2015 Florent BEAURAIN
// Last update Mon Nov  2 13:04:11 2015 Florent BEAURAIN
//

#include		"USocket.hpp"

/*
** Constructeurs & Destructeurs
*/

USocket::USocket(const int fd) {
	_fd = fd;
	_fd_max = fd;
	_FD_ZERO("rw");
}

USocket::~USocket(void) {
	_close();
}

/*
** Getters
*/

int					USocket::getfd(void) const {
	return _fd;
}

/*
** Méthodes
*/

void					USocket::_socket(const int socket_family, const int socket_type, const int protocol) {
	struct protoent		*pe;
	(void)protocol;

	if (socket_type == SOCK_STREAM) {
		if ((pe = getprotobyname("TCP")) == NULL)
			throw std::runtime_error(strerror(errno));
	}
	else if (socket_type == SOCK_DGRAM) {
		if ((pe = getprotobyname("UDP")) == NULL)
			throw std::runtime_error(strerror(errno));
	}
	else
		throw std::runtime_error("[Error] : bad protocol");

	if ((_fd = socket(socket_family, socket_type, pe->p_proto)) == -1) {
		throw std::runtime_error(strerror(errno));
		}

	_fd_max = _fd;
	_FD_ZERO("rw");

	return;
}

USocket				*USocket::_accept(void) {
	int						fd;
	struct sockaddr_in	s_in;
	socklen_t            sin_len = sizeof(s_in);

	if ((fd = accept(_fd, reinterpret_cast<struct sockaddr *>(&s_in), &sin_len)) == -1)
		throw std::runtime_error(strerror(errno));
	if (_fd_max < fd)
		_fd_max = fd;

	USocket	*newConnection = new USocket(fd);
	return newConnection;
}

void					USocket::_bind(const int socket_family, const int port) const {
	struct sockaddr_in	s_in;

	s_in.sin_family = socket_family;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = htons(INADDR_ANY);
	if (bind(_fd, reinterpret_cast<const struct sockaddr *>(&s_in), sizeof(s_in)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

void					USocket::_listen(const int backlog) const {
	if (listen(_fd, backlog) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}


void					USocket::_select(const int sec, const int usec) {
	struct timeval	tv;

  	tv.tv_sec = sec;
  	tv.tv_usec = usec;
	if (select(_fd_max + 1, &_readfds, &_writefds, NULL, &tv) == -1) {
		throw std::runtime_error(strerror(errno));
	}

	return;
}

void					USocket::_FD_ZERO(const std::string &mode) {
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

void					USocket::_FD_SET(const std::string &mode) {
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

void					USocket::_FD_SET(const ISocket * const socket, const std::string &mode) {
	if (mode == "r")
		FD_SET(socket->getfd(), &_readfds);
	else if (mode == "w")
		FD_SET(socket->getfd(), &_writefds);
	else if (mode == "rw") {
		FD_SET(socket->getfd(), &_readfds);
		FD_SET(socket->getfd(), &_writefds);
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_SET()");

	return;
}

bool					USocket::_FD_ISSET(const char mode) const {
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

bool					USocket::_FD_ISSET(const ISocket * const socket, const char mode) const {
	if (mode == 'r') {
		if (FD_ISSET(socket->getfd(), &_readfds))
			return true;
	}
	else if (mode == 'w') {
		if (FD_ISSET(socket->getfd(), &_writefds))
			return true;
	}
	else
		throw std::runtime_error("[Error]: bad mode for _FD_ISSET()");

	return false;
}

void					USocket::_close(void) const {
	if (close(_fd) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

char					*USocket::_recv(const int flags) const {
	char				*msg = new char[30721];
	ssize_t			ret;

	if ((ret = recv(_fd, msg, 30720, flags)) <= 0)
		throw std::runtime_error(strerror(errno));
	msg[ret] = '\0';

	return msg;
}

char					*USocket::_recv(const size_t size, const int flags) const {
	char				*msg = new char[size + 1];
	ssize_t			ret;

	if ((ret = recv(_fd, msg, size, flags)) <= 0)
		throw std::runtime_error(strerror(errno));
	msg[ret] = '\0';

	return msg;
}

void					USocket::_send(const char * const msg, const int flags) const {
	ssize_t			ret;

	if ((ret = send(_fd, msg, strlen(msg), flags)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

void					USocket::_send(const char * const msg, const size_t size, const int flags) const {
	ssize_t			ret;

	if ((ret = send(_fd, msg, size, flags)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

void					USocket::_send(const std::string &msg, const int flags) const {
	ssize_t			ret;

	if ((ret = send(_fd, msg.c_str(), msg.size(), flags)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}

void					USocket::_send(const std::string &msg, const size_t size, const int flags) const {
	ssize_t			ret;

	if ((ret = send(_fd, msg.c_str(), size, flags)) == -1)
		throw std::runtime_error(strerror(errno));

	return;
}
