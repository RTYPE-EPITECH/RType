#ifndef				__LOG_HPP__
# define				__LOG_HPP__

# include			<exception>
# include			<iostream>
# include			<fstream>

class					Log {
public:
	Log(void);
	~Log(void);

private:
	std::ofstream	_fileLog;

	void 				addLog(const std::string &str);
};

#endif				/* !__LOG_HPP__ */
