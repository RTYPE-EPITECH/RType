#include "UDynamicLibrary.hpp"
#include "IMonster.hpp"

template<typename T>
void	UDynamicLibrary<T>::loadLibrary(const std::string & begin)
{
  if ((this->_handle = dlopen(begin.c_str(), RTLD_NOW | RTLD_GLOBAL)) == NULL) {
    std::string	suite("./");
    suite.append(begin);
    if ((this->_handle = dlopen(suite.c_str(), RTLD_NOW | RTLD_GLOBAL)) == NULL)
      throw std::runtime_error(dlerror());
  }
}

template<>
void	UDynamicLibrary<IMonster *>::loadLibrary(const std::string & begin)
{
  if ((this->_handle = dlopen(begin.c_str(), RTLD_NOW | RTLD_GLOBAL)) == NULL) {
    std::string	suite("./");
    suite.append(begin);
    if ((this->_handle = dlopen(suite.c_str(), RTLD_NOW | RTLD_GLOBAL)) == NULL)
      throw std::runtime_error(dlerror());
  }
}


template<typename T>
T	UDynamicLibrary<T>::useFunction(void) const
{
  typedef T *(*maker_lib)();
  maker_lib * lib = (maker_lib*)dlsym(this->_handle, "getInstance");
  if (lib == NULL)
    throw std::runtime_error(dlerror());
  return (*lib)();
}

template<>
IMonster *	UDynamicLibrary<IMonster *>::useFunction(void) const
{
  typedef IMonster *(*maker_lib)();
  maker_lib  *lib =  (maker_lib*)dlsym(this->_handle, "getInstance");
  if (lib == NULL)
    throw std::runtime_error(dlerror());
  return (*lib)();
}


template<typename T>
void	UDynamicLibrary<T>::freeLibrary(void)
{
}

template<>
void	UDynamicLibrary<IMonster *>::freeLibrary(void)
{
}
