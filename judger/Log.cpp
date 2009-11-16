#include "Log.h"

#include "Common.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

Log _log;
EndLog endlog;

Log::Log(bool flag)
{
	bLogToStderr = flag;
	bLogging = false;

	path = "soj.log";
	fd = open(path.c_str(), O_CREAT|O_RDWR|O_APPEND, 0644);
	if(fd < 0)
	{
		fprintf(stderr, "log failed to open");
		exit(1);
	}
}

Log::~Log()
{
	if(bLogging)
		EndOneLog();
	close(fd);
}

ostringstream &Log::GetLogStream(int level)
{
	if(bLogging)
		EndOneLog();
	BeginOneLog();
	return logStream;
}

void Log::BeginOneLog()
{
	bLogging = true;//start logging

	logStream.str("");
	
	logStream<<GetTimeInString(LOG_TIME_FORMAT)<<" ";
}

void Log::EndOneLog()
{
	logStream<<endl;
	write(fd, logStream.str().c_str(), logStream.str().size());
	if(bLogToStderr)
		write(STDERR_FILENO, logStream.str().c_str(), logStream.str().size());

	bLogging = false;//end logging
}

ostream &operator<<(ostream &out, const EndLog &endLog)
{
	_log.EndOneLog();
	return out;
}

