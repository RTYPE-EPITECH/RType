#ifndef		__WDYNAMICLIBRARY_HPP__
# define	__WDYNAMICLIBRARY_HPP__

#include	<Windows.h>
#include	"IDynamicLibrary.hpp"

typedef int(__cdecl *MYPROC)(LPWSTR);

class		WDynamicLibrary : public IDynamicLibrary {
private:
	HINSTANCE hinstLib;
public:
	WDynamicLibrary(void);
	virtual ~WDynamicLibrary(void);

	virtual void	loadLibrary(const std::string &);
	virtual void	useFunction(const std::string &) const;
	virtual void	freeLibrary(void);
};

#endif // !__WDYNAMICLIBRARY_HPP__
