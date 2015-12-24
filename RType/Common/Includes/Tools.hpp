#ifndef					_TOOL_HPP_
# define				_TOOL_HPP_

#include				<sstream>
#include				<string>
#include				"EObject.hpp"
#include				"EMissile.hpp"

class					Tools {
public:
	Tools()  {}
	~Tools() {}

  template<typename T>
  static T			charToNumber(const std::string & nb)
  {
    std::istringstream	iss(nb.c_str());
    T			result;

    iss >> result;
    return (result);
  }

	template<typename T>
  static std::string		NumberToString(T nb)
  {
    std::ostringstream	oss;
    std::string		result;

    oss << nb;

    result = oss.str();
    return (result);
  }

  static std::string getName(EObject type, size_t id);
  static std::string EObjectToString(EObject);
  static std::string EMissileToString(EMissile);
};

#endif					/* _TOOL_HPP_ */
