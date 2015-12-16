#ifndef		__WDYNAMICLIBRARY_HPP__
# define	__WDYNAMICLIBRARY_HPP__

#include	<Windows.h>
#include	"IDynamicLibrary.hpp"

typedef int(__cdecl *MYPROC)(LPWSTR);

template <typename T>
class		WDynamicLibrary : public IDynamicLibrary<T> {
private:
	HINSTANCE hinstLib;
public:
	WDynamicLibrary(void) {}
	virtual ~WDynamicLibrary(void) {}

	virtual void	loadLibrary(const std::string &);
	virtual T		useFunction(void) const;
	virtual void	freeLibrary(void);
};


#endif // !__WDYNAMICLIBRARY_HPP__
