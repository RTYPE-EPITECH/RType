#include "MonsterFactory.hpp"
#include "Monster.hpp"
#include "Tools.hpp"
#ifdef _WIN32
#include "WDynamicLibrary.hpp"
#else
#include "UDynamicLibrary.hpp"
#endif


MonsterFactory::MonsterFactory()
{
}

MonsterFactory::~MonsterFactory()
{
}

MonsterFactory * MonsterFactory::getInstance()
{
	static MonsterFactory * o = new MonsterFactory();
	return o;
}

bool MonsterFactory::addLibrary(const std::string & m)
{
	IDynamicLibrary<IMonster *> * o = NULL;
#ifdef _WIN32
	o = new WDynamicLibrary<IMonster *>();
#else
	o = new IDynamicLibrary<IMonster *>();
#endif
	try
	{
		o->loadLibrary(m);
		IMonster * tmp = o->useFunction();
		Monster * tmp2 = new Monster();
		tmp2->loadIMonster(tmp);
		gen[tmp2->getTypeMonster()] = o;
		_listMonster.push_back(tmp2->getTypeMonster());
	}
	catch (const std::runtime_error & e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

Monster	* MonsterFactory::getInstance(const std::string & m)
{
	if (gen.count(m) > 0)
	{
		Monster * mo = new Monster();
		IMonster * im = gen[m]->useFunction();
		mo->loadIMonster(im);
		delete(im);
		return mo;
	}
	throw std::runtime_error("Invalid instance monster");
	return NULL;
}

std::vector<std::string> & MonsterFactory::getAllMonsterName()
{
	return _listMonster;
}