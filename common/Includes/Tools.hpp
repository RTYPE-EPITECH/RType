#ifndef					_TOOL_HPP_
# define				_TOOL_HPP_

#include				<sstream>
#include				<string>

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

 /* template<typename T>
  static std::string		NumberToString(T nb)
  {
    std::ostringstream	oss;
    std::string		result;

    oss << T;

    result = oss.str();
    return (result);
  }*/
};
/*template<unsigned int> unsigned int Tools::charToNumber(const std::string &);
template<unsigned short> unsigned short Tools::charToNumber(const std::string &);
template<int> int Tools::charToNumber(const std::string &);
template<short> short Tools::charToNumber(const std::string &);*/

#endif					/* _TOOL_HPP_ */
