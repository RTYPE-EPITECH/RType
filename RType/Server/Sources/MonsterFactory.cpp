#include "MonsterFactory.hpp"
#ifdef _WIN32
#include "WDynamicLibrary.hpp"
#else
#include "UDynamicLibrary.hpp"
#endif
#include "Monster.hpp"

MonsterFactory::MonsterFactory()
{
}

MonsterFactory::~MonsterFactory()
{
}

bool MonsterFactory::addLibrary(const std::string & m)
{
	IDynamicLibrary * o = NULL;
#ifdef _WIN32
	o = new WDynamicLibrary();
#else
	o = new IDynamicLibrary();
#endif
	try
	{
		o->loadLibrary(m);
	}
	catch (const std::runtime_error & e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	gen[m] = o;
	return true;
}

Monster	* MonsterFactory::getInstance(const std::string & m)
{
	if (gen.count(m) > 0)
	{
		gen[m]->useFunction("getInstance");
	}
	throw std::runtime_error("Invalid instance monster");
	return NULL;
}