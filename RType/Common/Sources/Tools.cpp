#include				"Tools.hpp"
#include				<map>

std::string Tools::getName(EObject type, size_t id)
{
	std::stringstream oss;

	oss << EObjectToString(type);
	oss << "-" << id;
	return std::string(oss.str());
}

std::string Tools::EObjectToString(EObject t)
{
	static std::map<EObject, std::string> gen;
	static bool check = true;

	if (check) {
		gen[PLAYER] = "player";
		gen[MISSILE] = "missile";
		gen[OBSTACLE] = "obstacle";
		gen[MONSTER] = "monster";
		gen[UNKNOWN_OBJECT] = "unknown";
		check = false;
	}
	if (gen.count(t) > 0)
		return gen.at(t);
	return gen[UNKNOWN_OBJECT];
}

std::string Tools::EMissileToString(EMissile t)
{
	static std::map<EMissile, std::string> gen;
	static bool check = true;

	if (check) {
		gen[NORMAL] = "normal";
		gen[STRONG] = "strong";
		gen[ONESHOT] = "oneshot";
		gen[UNKNOW_MISSILE] = "unknow";
		check = false;
	}
	if (gen.count(t) > 0)
		return gen.at(t);
	return gen[UNKNOW_MISSILE];
}