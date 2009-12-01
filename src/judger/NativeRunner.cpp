#include "NativeRunner.h"
#include "RunStruts.h"
#include "Log.h"
#include "Judger.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

void sigalrm_handler(int) {
}

int IgnoreSIGALRM() {
    struct sigaction act;
    act.sa_handler = sigalrm_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);
    return 0;
}

int __install_ignore_sigalrm_handler = IgnoreSIGALRM();

void NativeRunner::SetRunInfo(const RunInfo &info)
{
	runInfo.pathname = info.pathname;
	runInfo.inputFilename = info.inputFilename;
	runInfo.outputFilename = info.outputFilename;
	runInfo.runLimits = info.runLimits;
}

bool NativeRunner::Run()
{
	pid = fork();
	if(pid < 0)
	{
		log(Log::WARNING)<<"NativeRunner::Run : fork failed."<<strerror(errno)<<endlog;
		return false;
	}
	if(pid == 0)
	{
		if(!SetupChild())
		{
			log(Log::WARNING)<<"NativeRunner::Run : Setup child failed. "<<strerror(errno)<<endlog;
		}
		exit(0);
	}
	else
	{
		sandbox->SetChildPid(pid);
		sandbox->Watch();
		if(sandbox->IsNormalExit())
		{
			return true;
		}
		else
		{
			if(sandbox->IsTermByRestrictedSyscall())
			{
				result = RUNTIME_ERROR;
				return false;
			}
			int status = sandbox->GetExitStatus();
			if(WIFSIGNALED(status))
			{
				switch(WTERMSIG(status))
				{
				case SIGABRT:
				case SIGBUS:
				case SIGFPE://float point exception
				case SIGILL://invalid hardware instruction
				case SIGSYS://invalid syscall
					result = RUNTIME_ERROR;
					break;
				case SIGSEGV://both access violation and memory limit exceeded with lead to this
					if(sandbox->GetRunUsage()->memory >= runInfo.runLimits.memory)
						result = MEMORY_LIMIT_EXCEEDED;
					else
						result = RUNTIME_ERROR;
					break;
				case SIGKILL:
				case SIGTERM:
					result = RUNTIME_ERROR;
					dlog<<"NativeRunner::Run SIGKILL or SIGTERM cause child terminated."<<endlog;
					break;
				case SIGXCPU://cputime limit exceed
					result = TIME_LIMIT_EXCEEDED;
					break;
				case SIGXFSZ://fsize limit exceeded
					result = OUTPUT_LIMIT_EXCEEDED;
					break;
				default:
					dlog<<"NativeRunner::Run Unexpected signal: "<<WTERMSIG(status)<<endlog;
				}
			}
			else
			{
				//how do we come here?
				dlog<<"NativeRunner::Run Unexpected exit status: "<<status<<endlog;
			}
			return false;
		}
	}
}

bool NativeRunner::SetupChild()
{
	//setup input and output
	int fd_input = open(runInfo.inputFilename.c_str(), O_RDONLY);
	if(fd_input < 0)
		return false;
	int fd_output = open(runInfo.outputFilename.c_str(), O_WRONLY);
	if(fd_output < 0)
		return false;
	int fd_err = open(runInfo.errFilename.c_str(), O_WRONLY);
	if(fd_err < 0)
		return false;
	int ret;
	ret = dup2(fd_input, STDIN_FILENO);
	if(ret < 0)
		return false;
	dup2(fd_output, STDOUT_FILENO);
	if(ret < 0)
		return false;
	dup2(fd_output, STDERR_FILENO);
	if(ret < 0)
		return false;

	ret = execl(runInfo.pathname.c_str(), NULL, NULL);
	if(ret < 0)
		return false;

	return true;
}
