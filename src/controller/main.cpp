#include "Controller.h"
#include "Util.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

using namespace std;

bool bDaemon = false;
bool bSingleton = false;

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
        perror("getrlimit error.\n");
        exit(0);
	}

	if((pid = fork()) < 0)
	{
        perror("Daemonize():fork failed!\n");
		exit(0);
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
        exit(0);
    }
	else if ( pid != 0)
		exit(0);

	//here we are
	//if(chroot("/"))
	//	return false;
	
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
        perror("open error.\n");
        exit(0);
	}
	return 0;
}

#define LOCKFILE "/var/run/controller.pid"
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
		perror("Can't open lock\n");
        exit(0);
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
            perror("Lock error!\n");
            exit(0);
        }
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf + 1));
	return 0;
}


void ParseArgs(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-deamon") == 0)
        {
            bDaemon = true;
        }
        else if(strcmp(argv[i], "-single") == 0)
        {
            bSingleton = true;
        }
        else
        {
            cerr<<"Usage: controller [-single] [-daemon]\n"<<endl;
            exit(0);
        }
    }
}

void SigIntHandler(int)
{
    Controller::GetInstance().bStopped = true;
}

int main(int argc, char *argv[])
{
    ParseArgs(argc, argv);
    Signal(SIGINT, SigIntHandler);

    if(bSingleton)
    {
        if(AlreadyRunning() > 0)
        {
            cerr<<"Another instance is running!"<<endl;
            exit(0);
        }
    }
    if(bDaemon)
    {
        Daemonize();
    }
    Controller &c = Controller::GetInstance();
    if(c.Init() < 0)
    {
        cerr<<"Initialization failed."<<endl;
        exit(0);
    }
    c.Loop();
    c.CleanUp();
}
