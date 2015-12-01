#ifndef HANDLETHREAD_HPP_
#define	HANDLETHREAD_HPP_

class IThread;
class Game;

class HandleThread {
private:
	IThread * _t;
public:
	bool init(Game * cl);
	bool destroy(Game * cl);
	bool destroyAll();
	static void *functionClient(void * arg);
};

#endif  /*HANDLETHREAD_HPP_*/