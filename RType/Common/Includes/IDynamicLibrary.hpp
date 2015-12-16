#ifndef			__IDYNAMICLIBRARY_HPP__
# define		__IDYNAMICLIBRARY_HPP__

#include		<iostream>

template <typename T>
class			IDynamicLibrary {
public:
	virtual		~IDynamicLibrary(void) {};
	virtual void	loadLibrary(const std::string &) = 0;
<<<<<<< HEAD
	virtual T		useFunction(void) const = 0;
=======
	virtual T		useFunction() const = 0;
>>>>>>> f599891f4e2957201056a62617dd613aa2293798
	virtual void	freeLibrary(void) = 0;
};

#endif