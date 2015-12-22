#ifndef _UDYNAMICLIBRARY_HPP
# define _UDYNAMICLIBRARY_HPP

#include "IDynamicLibrary.hpp"
#include <dlfcn.h>
#include <stdexcept>

template<typename T>
class		UDynamicLibrary : public IDynamicLibrary<T>
{
public:
  UDynamicLibrary() {};
  virtual ~UDynamicLibrary(void) {};
  virtual void	loadLibrary(const std::string &);
  virtual T	useFunction(void) const;
  virtual void	freeLibrary(void);
private:
  void * _handle;
};

#endif // _UDYNAMICLIBRARY_HPP
