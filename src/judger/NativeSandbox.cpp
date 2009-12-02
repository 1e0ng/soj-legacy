#include "NativeSandbox.h"
#include "Log.h"
#include "Common.h"

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
	while(true)
	{
		int ret = waitpid(-1, &status, 0);
		if(ret < 0)//wrong pid?
		{
			log(Log::ERROR)<<"NativeSandbox:Waitpid failed."<<strerror(errno)<<endlog;
			bRunning = false;
			break;
		}
		if(WIFEXITED(status))
		{
			bNormalExit = true;
			bRunning = false;
			log(Log::INFO)<<"NativeSandbox:Child exited."<<endlog;
			break;
		}
		else if(WIFSIGNALED(status))
		{
			bNormalExit = false;
			bRunning = false;
			log(Log::INFO)<<"NativeSandbox:Child was terminated by signal "<<WTERMSIG(status)<<endlog;
			break;
		}
		else if(WIFSTOPPED(status))
		{
			int sig = WSTOPSIG(status);
			if(sig != SIGTRAP)//stop by other signal rather than SYSTRAP, for example SIGTTOU
			{
				ptrace(PTRACE_SYSCALL, pid, 0, sig);
				continue;
			}
			struct user_regs_struct regs;
			ptrace(PTRACE_GETREGS, pid, 0, &regs);
			if(regs.orig_eax == SYS_exit || regs.orig_eax == SYS_exit_group)
			{
				//log(Log::INFO)<<"exit or exit_group called"<<endl;
			}
			if(!watcher.IsSyscallAllowed(regs.orig_eax, &regs))
			{
				ptrace(PTRACE_KILL, pid, NULL, NULL);
				bNormalExit = false;
				bRunning = false;
				bTermByRestrictedSyscall = true;
				break;
			}
			else
			{
				ptrace(PTRACE_SYSCALL, pid, 0, 0);
			}
		}
		else
		{
			dlog<<"Unknown status "<< hex <<status<<endlog;
		}
	}
	UpdateRunUsage();
}

void NativeSandbox::SetChildPid(int pid)
{
	this->pid = pid;
	watcher.SetChildPid(pid);
	memset(&ru, 0, sizeof(ru));
}

bool NativeSandbox::UpdateRunUsage()
{
	return false;
}
