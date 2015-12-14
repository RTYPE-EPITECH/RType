#include		"WDynamicLibrary.hpp"

WDynamicLibrary::WDynamicLibrary(void) {}

WDynamicLibrary::~WDynamicLibrary(void) {}

void			WDynamicLibrary::loadLibrary(const std::string &lib) {
	if ((this->hinstLib = LoadLibrary((LPCWSTR)lib.data())) == NULL)
		throw std::runtime_error("[DynamicLibrary] LoadLibrary failed");
}

void			WDynamicLibrary::useFunction(const std::string &func) const {
	MYPROC		ProcAdd = (MYPROC)GetProcAddress(this->hinstLib, (LPCSTR)func.data());
	if (ProcAdd == NULL)
		throw std::runtime_error("[DynamcLibrary] GetProcAdress failed");
	ProcAdd(L"");
}

void			WDynamicLibrary::freeLibrary(void) {
	FreeLibrary(this->hinstLib);
}