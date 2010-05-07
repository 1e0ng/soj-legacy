#include "Log.h"

#include "Common.h"
#include "Configuration.h"

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
}

int Log::Initialize()
{
	path = Configuration::GetInstance().GetLogPathname();
    char buf[256] = {0};
    sprintf(buf, "%s/soj-%s-%d.log", path.c_str(), GetTimeInString(NUMBER_TIME_FORMAT).c_str(), getpid());
	fd = open(buf, O_CREAT|O_RDWR|O_APPEND, 0644);
	if(fd < 0)
	{
		perror("log failed to open");
		return -1;
	}
	return 0;
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

