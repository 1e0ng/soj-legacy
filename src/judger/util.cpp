#include "util.h"
#include "RunStruts.h"
#include "Log.h"
#include "Configuration.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/ptrace.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/resource.h>

using namespace std;

bool SetRLimit(int resource, rlim_t limit)
{
	rlimit rl;
	rl.rlim_cur = limit;
	rl.rlim_max = limit + 1;
	return setrlimit(resource, &rl) != -1;
}

//the two functions below are copied from zoj with slight changes
//
//returns the time consumed by process pid in ms
/*
int ReadTimeConsumption(pid_t pid) {


    char buffer[64];
    sprintf(buffer, "/proc/%d/stat", pid);
    FILE* fp = fopen(buffer, "r");
    if (fp == NULL) {
        return -1;
    }
    int utime, stime;
    while (fgetc(fp) != ')');
    fgetc(fp);
    if (fscanf(fp, "%*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %d %d", &utime, &stime) < 2) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    static int clktck = 0;
    if (clktck == 0) {
        clktck = sysconf(_SC_CLK_TCK);
    }
    return int((utime + stime + 0.0) / clktck * 1000);

}

int ReadMemoryConsumption(pid_t pid) {

    char buffer[64];
    sprintf(buffer, "/proc/%d/status", pid);
    FILE* fp = fopen(buffer, "r");
    if (fp == NULL) {
        return -1;
    }
    int vmPeak = 0, vmSize = 0, vmExe = 0, vmLib = 0, vmStack = 0;
    while (fgets(buffer, 32, fp)) {
        if (!strncmp(buffer, "VmPeak:", 7)) {
            sscanf(buffer + 7, "%d", &vmPeak);
        } else if (!strncmp(buffer, "VmSize:", 7)) {
            sscanf(buffer + 7, "%d", &vmSize);
        } else if (!strncmp(buffer, "VmExe:", 6)) {
            sscanf(buffer + 6, "%d", &vmExe);
        } else if (!strncmp(buffer, "VmLib:", 6)) {
            sscanf(buffer + 6, "%d", &vmLib);
        } else if (!strncmp(buffer, "VmStk:", 6)) {
            sscanf(buffer + 6, "%d", &vmStack);
        }
    }
    fclose(fp);
    if (vmPeak) {
        vmSize = vmPeak;
    }
    return vmSize - vmExe - vmLib - vmStack;

}

bool GetCurrentRunUsage(pid_t pid, RunUsage &ru)
{
	struct rusage buf;
	getrusage(RUSAGE_CHILDREN, &buf);
	
	ru.time=buf.ru_utime.tv_sec*1000+buf.ru_stime.tv_sec*1000+buf.ru_stime.tv_usec/1000+buf.ru_utime.tv_usec/1000;//the unit of ru.time is ms
	
	ru.memory= buf.ru_minflt*(sysconf(_SC_PAGESIZE)/1024);//divide 1024 to make the unit be KB
	log(Log::INFO)<<"Run memory is: "<<ru.memory<<endlog;
	log(Log::INFO)<<"Run memory is: "<<buf.ru_minflt<<endlog;
	
	//ru.time = ReadTimeConsumption(pid);
	if(ru.time < 0){
		ru.time=0;
		return false;
	}
	//ru.memory = ReadMemoryConsumption(pid);
	if(ru.memory < 0){
		ru.memory=0;
		return false;
	}
	return true;
}
*/

int PeekStringFromProc(int pid, unsigned long address, char *buf, size_t size)
{
	long mask = -1<<2;//we use long as a word
	long data = 0;
	size_t i = 0;

	if(address & mask)
	{
		int base = address & mask;
		int offset = address & ~mask;
		data = ptrace(PTRACE_PEEKDATA, pid, base, 0);
		if(data < 0)
			return -1;
		for(i = 0; i < size && (offset + i < sizeof(long)) ; i++)
		{
			buf[i] = ((char *)&data)[offset + i];
			if(buf[i] == '\0')
				goto done;
		}
		address = base + ~mask + 1;
	}
	for(; i < size; address += sizeof(long))
	{
		data = ptrace(PTRACE_PEEKDATA, pid, address, 0);
		if(data < 0)
			return -1;
		for(size_t j = 0; j < sizeof(long) && i < size; j++, i++)
		{
			buf[i] = ((char *)&data)[j];
			if(buf[i] == '\0')
				goto done;
		}
	}
done:
	buf[size] = '\0';
	return i; 
}


//return 0 on success
//return -1 on fail
int Daemonize()
{
	int i, pid, fd0, fd1, fd2;
	struct rlimit rl;
	struct sigaction sa;

	umask(0);

	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		return -1;
	}

	if((pid = fork()) < 0)
	{
        perror("Daemonize():fork failed!\n");
		return -1;
	}
	else if( pid != 0)
	{
		exit(0);//parent
	}

	setsid();//start new session

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
		return -1;
	if((pid = fork() ) < 0)
    {
        perror("Daemonize():fork failed!\n");
		return -1;
    }
	else if ( pid != 0)
		exit(0);

	if(chroot(Configuration::GetInstance().GetRootPath().c_str()))
		return -1;
	
	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for(i = 0; (unsigned)i < rl.rlim_max; i++)
		close(i);

	//attach file descriptors 0, 1 and 2 to /dev/null
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		return -1;
	}
	return 0;
}

#define LOCKFILE "/var/run/judger.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int LockFile(int fd) {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    return fcntl(fd, F_SETLK, &lock);
}

//return 0 if there's no other instance running
//return 1 if there's other instance running
//return -1 on fail
int AlreadyRunning()
{
	int fd;
	char buf[16];

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0)
	{
		log(Log::ERROR)<<"Can't open lock "<<LOCKFILE<<" "<<strerror(errno)<<endlog;
		return -1;
	}
	if(LockFile(fd) < 0)
	{
		if(errno == EACCES || errno == EAGAIN)
		{
            //other instance is running
			close(fd);
			return 1;
		}
        else
        {
		    log(Log::ERROR)<<"Can't lock "<<LOCKFILE<<" "<<strerror(errno)<<endlog;
		    return -1;
        }
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf + 1));
	return 0;
}


int InstallSignalHandler(int signum, sighandler_t handler)
{
	struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    return sigaction(signum, &sa, NULL);
}


string GetLanName(int lan)
{
	switch(lan)
	{
	case 1:return "c++";
	case 2:return "c";
	case 3:return "java";
	default:return "";
	}
}

string GetLanExt(int lan)
{
	switch(lan)
	{
	case 1:return "cpp";
	case 2:return "c";
	case 3:return "java";
	default:return "";
	}
}
