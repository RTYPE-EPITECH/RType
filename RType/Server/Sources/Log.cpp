#include			"Log.hpp"

/*
** Constructeurs & Destructeurs
*/

Log::Log(void) {
	_fileLog.open("server.log", std::ios::out | std::ios::trunc);
	if (_fileLog.fail() == true)
		throw std::runtime_error("[Error]: Can't open log file");
}

Log::Log(const std::string & e) {
	_fileLog.open(e.c_str(), std::ios::out | std::ios::trunc);
	if (_fileLog.fail() == true)
		throw std::runtime_error("[Error]: Can't open log file");
}

Log::~Log(void) {
	_fileLog.close();
}

/*
** Méthodes
*/

void 				Log::addLog(const std::string &str) {
	_fileLog.write(str.c_str(), str.size());
	_fileLog.write("\n", 1);
}
