#ifndef			__IDYNAMICLIBRARY_HPP__
# define		__IDYNAMICLIBRARY_HPP__

#include		<iostream>

class			IDynamicLibrary {
public:
	virtual		~IDynamicLibrary(void) {};
	virtual void	loadLibrary(const std::string &) = 0;
	virtual void	useFunction(const std::string &) const = 0;
	virtual void	freeLibrary(void) = 0;
};

#endif