#ifndef				__LOG_HPP__
# define				__LOG_HPP__

# include			<exception>
# include			<iostream>
# include			<fstream>
# include			<string>

class					Log {
public:
	Log(void);
	Log(const std::string &);
	~Log(void);

	void addLog(const std::string & str);
private:
	std::ofstream	_fileLog;
	std::string name;
};

#endif				/* !__LOG_HPP__ */
