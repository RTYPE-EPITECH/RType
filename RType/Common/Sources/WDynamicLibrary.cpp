#include		"WDynamicLibrary.hpp"

template <typename T>
WDynamicLibrary<T>::WDynamicLibrary(void) {}

template <typename T>
WDynamicLibrary<T>::~WDynamicLibrary(void) {}

template <typename T>
void			WDynamicLibrary<T>::loadLibrary(const std::string &lib) {
	if ((this->hinstLib = LoadLibrary((LPCWSTR)lib.data())) == NULL)
		throw std::runtime_error("[DynamicLibrary] LoadLibrary failed");
}

template <typename T>
T				WDynamicLibrary<T>::useFunction(void) const {
	MYPROC		ProcAdd = (MYPROC)GetProcAddress(this->hinstLib, (LPCSTR)"getInstance()");
	if (ProcAdd == NULL)
		throw std::runtime_error("[DynamcLibrary] GetProcAdress failed");
	return (ProcAdd(""));
}

template <typename T>
void			WDynamicLibrary<T>::freeLibrary(void) {
	FreeLibrary(this->hinstLib);
}