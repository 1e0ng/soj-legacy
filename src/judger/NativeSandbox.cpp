#include "NativeSandbox.h"
#include "Log.h"
#include "Common.h"
#include "util.h"

#include <string.h>
#include <cstdlib>
#include <errno.h>
#include <cstdio>
//#include <unistd.h>
#include <sys/wait.h>
#include <syscall.h>
//#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>

using namespace std;

NativeSandbox::NativeSandbox()
{
	pid = 0;
	status = 0;
	bNormalExit = false;
	bRunning = false;
	bTermByRestrictedSyscall = false;
}

void NativeSandbox::Watch()
{
	bRunning = true;
	bool firstCall = true;
	while(true)
	{
		int ret = waitpid(-1, &status, 0);
		//log(Log::INFO)<<"catch child at status: "<<status<<endlog;
		if(ret < 0)//wrong pid?
		{
			log(Log::INFO)<<"NativeSandbox:Waitpid failed."<<strerror(errno)<<endlog;
			bRunning = false;
			break;
		}
		
		if(WIFEXITED(status))
		{
			bNormalExit = true;
			bRunning = false;
			log(Log::INFO)<<"NativeSandbox:Child exited."<<endlog;
			UpdateRunUsage();
			break;
		}
		else if(WIFSIGNALED(status))
		{
			bNormalExit = false;
			bRunning = false;
			int sig = WTERMSIG(status);
			int wt=ptrace(PTRACE_SYSCALL,pid,0,sig);
			//int wt=kill(pid,9);
			//log(Log::INFO)<<"child pid: "<<pid<<endlog;
			wait(&wt);
			log(Log::INFO)<<"NativeSandbox:Child was terminated by signal "<<WTERMSIG(status)<<endlog;
			break;
		}
		else if(WIFSTOPPED(status))
		{
			//log(Log::INFO)<<"Child process stopped."<<endlog;
			
			int sig = WSTOPSIG(status);
			if(sig != SIGTRAP)//stop by other signal rather than SYSTRAP, for example SIGTTOU
			{
				log(Log::INFO)<<"Stoped by other signal."<<endlog;
				ptrace(PTRACE_SYSCALL, pid, 0, sig);
				continue;
			}
			struct user_regs_struct regs;
			ptrace(PTRACE_GETREGS, pid, 0, &regs);
			if(regs.orig_eax == SYS_exit || regs.orig_eax == SYS_exit_group)
			{
				//log(Log::INFO)<<"exit or exit_group called"<<endl;
			}
			if(regs.orig_eax == SYS_open ||regs.orig_eax == SYS_close){
				ptrace(PTRACE_SYSCALL,pid,0,0);
			}
			else if(!firstCall&&!watcher.IsSyscallAllowed(regs.orig_eax, &regs))
			{
				bNormalExit = false;
				bRunning = false;
				bTermByRestrictedSyscall = true;
				log(Log::INFO)<<"Child was killed because of restricted syscall."<<endlog;
				ptrace(PTRACE_KILL, pid, NULL, NULL);
				break;
			}
			else
			{
				ptrace(PTRACE_SYSCALL, pid, 0, 0);
			}
		}
		else
		{
			log(Log::INFO)<<"Unknown status "<< hex <<status<<endlog;
		}
		firstCall=false;
	}
}

void NativeSandbox::SetChildPid(int pid)
{
	this->pid = pid;
	watcher.SetChildPid(pid);
	//memset(&ru, 0, sizeof(ru));
}

bool NativeSandbox::UpdateRunUsage()
{
	struct rusage buf;
	getrusage(RUSAGE_CHILDREN, &buf);
	ru.time=buf.ru_utime.tv_sec*1000+buf.ru_stime.tv_sec*1000+buf.ru_stime.tv_usec/1000+buf.ru_utime.tv_usec/1000;
	//the unit of ru.time is ms
	ru.memory=buf.ru_minflt*(sysconf(_SC_PAGESIZE)/1024);
	//divide 1024 to make the unit be KB
	if(ru.time<0||ru.memory<0){
		log(Log::INFO)<<"run time or run memory is less than 0: "<<ru.time<<endlog;
		ru.time=0,ru.memory=0;
		return false;
	}
	return true;	
}
