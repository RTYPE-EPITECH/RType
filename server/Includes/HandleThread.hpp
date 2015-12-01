#ifndef HANDLETHREAD_HPP_
#define	HANDLETHREAD_HPP_

class IThread;
class Client;

class HandleThread {
private:
	IThread * _t;
public:
	bool init(Client * cl);
	bool destroy(Client * cl);
	bool destroyAll();
	static void *functionClient(void * arg);
};

#endif  /*HANDLETHREAD_HPP_*/