#ifndef					_TOOL_HPP_
# define				_TOOL_HPP_

#include				<sstream>

class					Tools {
public:
	Tools()  {}
	~Tools() {}
	template<typename T>
	static T charToNumber(char * nb)
	{
		std::istringstream	iss(nb);
		T			result;

		iss >> result;
		return (result);
	}
};

//template<unsigned int> unsigned int Tools::charToNumber(char *);

#endif					/* _TOOL_HPP_ */