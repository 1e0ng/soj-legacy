#ifndef LOG_H
#define LOG_H

#include <string>
#include <sstream>

class Log
{
public:
	enum{DEBUG, INFO, WARNING, ERROR, CRITICAL};

	Log(bool flag = true);
	~Log();
	int Initialize();

	std::ostringstream &GetLogStream(int level = DEBUG);
	void BeginOneLog();
	void EndOneLog();
private:
	int fd; //the fileno of the log file
	std::string path; //path of the log file
	bool bLogToStderr;
	bool bLogging;		//whether we are writing a log 
	std::ostringstream logStream;
};
//just indicates the end of one log
class EndLog{};

//here are the user interface
extern Log _log;
#define dlog _log.GetLogStream()
#define log(level) _log.GetLogStream(level)
extern EndLog endlog;

std::ostream &operator<<(std::ostream &out, const EndLog &endLog);

#endif//LOG_H
