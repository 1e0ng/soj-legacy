#include "NativeRunner.h"
#include "RunStruts.h"
#include "Log.h"
#include "Judger.h"
#include "util.h"

#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/ptrace.h>

using namespace std;

void sigalrm_handler(int) {
}

int __install_ignore_sigalrm_handler = InstallSignalHandler(SIGALRM, sigalrm_handler);

const RunUsage NativeRunner::GetRunUsage()const
{
	return ru;
}

void NativeRunner::SetRunInfo(const RunInfo &info)
{
	runInfo = info;
}

void NativeRunner::SetTimeLimit(long time)
{
	runInfo.runLimits.time = time;
}

void NativeRunner::SetMemoryLimit(long memory)
{
	runInfo.runLimits.memory = memory;
	runInfo.runLimits.vm = memory + 10 * 1024 * 1024;
}

bool NativeRunner::Run(int proid, int rid)
{
	pid = fork();
	if(pid < 0)
	{
		log(Log::WARNING)<<"NativeRunner::Run : fork failed."<<strerror(errno)<<endlog;
		return false;
	}
	if(pid > 0){//parent
		waitpid(0,0,0);
		exit(0);
	}
	if(pid==0){//child
		int pid2= fork();
		if(pid2 < 0)
		{
			log(Log::WARNING)<<"NativeRunner::Run : fork2 failed."<<strerror(errno)<<endlog;
			return false;
		}
		if(pid2 == 0)//grandson
		{
			if(!SetupChild(proid, rid))
			{
				log(Log::WARNING)<<"NativeRunner::Run : Setup child failed. "<<strerror(errno)<<endlog;
				exit(0);
			}
		}
		else{
			sandbox->SetChildPid(pid2);
			sandbox->Watch();
			ru=sandbox->GetRunUsage();
		
			if(sandbox->IsNormalExit())
			{
				int status = sandbox->GetExitStatus();
				if(WEXITSTATUS(status) == 0)
				{
					result = OK;
					return true;
				}
				else
				{
					result = SYS_ERROR;
					log(Log::WARNING)<<"Child exited with "<<WEXITSTATUS(status)<<" ."<<endlog;
					return true;
				}
			}
			else
			{
				if(sandbox->IsTermByRestrictedSyscall())
				{
					result = RESTRICTED_SYSCALL;
					log(Log::INFO)<<"result= "<<result<<endlog;
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
						if((unsigned)ru.memory >= runInfo.runLimits.memory)
							result = MEMORY_LIMIT_EXCEEDED;
						else
							result = RUNTIME_ERROR;
						break;
					case SIGKILL:
					case SIGTERM:
						result = RUNTIME_ERROR;
						log(Log::INFO)<<"NativeRunner::Run SIGKILL or SIGTERM cause child terminated."<<endlog;
						break;
					case SIGXCPU://cputime limit exceed
						result = TIME_LIMIT_EXCEEDED;
						break;
					case SIGXFSZ://fsize limit exceeded
						result = OUTPUT_LIMIT_EXCEEDED;
						break;
					default:
						log(Log::INFO)<<"NativeRunner::Run Unexpected signal: "<<WTERMSIG(status)<<endlog;
					}
				}
				else
				{
					//how do we come here?
					log(Log::INFO)<<"NativeRunner::Run Unexpected exit status: "<<status<<endlog;
				}
			}
		}
	}
	return true;
}

bool NativeRunner::SetupChild(int pid, int rid)
{
	log(Log::INFO)<<"Seting up child..."<<endlog;
	//setup input and output
	char tmp[512],tmp2[512];
	close(0);close(1);close(2);
	sprintf(tmp, "%s/%d", runInfo.inputPath.c_str(), pid);
	int fd_input = open(tmp, O_RDONLY);
	if(fd_input < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to open input file "<< tmp <<" ."<<endlog;
		return false;
	}
	sprintf(tmp, "%s/%d", runInfo.outputPath.c_str(), rid);
	int fd_output = open(tmp, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd_output < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to open output file "<< tmp << ". "<<endlog;
		return false;
	}
	int fd_err = open("/dev/null", O_RDWR);
	if(fd_err < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to open error file."<<endlog;
		return false;
	}
	int ret;
	ret = dup2(fd_input, STDIN_FILENO);
	if(ret < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to dup stdin"<<endlog;
		return false;
	}
	dup2(fd_output, STDOUT_FILENO);
	if(ret < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to dup stdout"<<endlog;
		return false;
	}
	dup2(fd_output, STDERR_FILENO);
	if(ret < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to dup stderr"<<endlog;
		return false;
	}

	log(Log::INFO)<<"Dup OK"<<endlog;
	if(runInfo.runLimits.time)
	{
		if(SetRLimit(RLIMIT_CPU, runInfo.runLimits.time/1000) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set cpu limit to "<<runInfo.runLimits.time<<"."<<endlog;
			return false;
		}
	}
	log(Log::INFO)<<"Time limit is set."<<endlog;
	if(runInfo.runLimits.memory)
	{
		if(SetRLimit(RLIMIT_DATA, runInfo.runLimits.memory) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set data limit to "<<runInfo.runLimits.memory<<"."<<endlog;
			return false;
		}
	}
	log(Log::INFO)<<"Memory limit is set."<<endlog;
	/*
	if(runInfo.runLimits.vm)
	{
		if(SetRLimit(RLIMIT_AS, runInfo.runLimits.vm) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set as limit to "<<runInfo.runLimits.vm<<"."<<endlog;
			return false;
		}
	}
	if(runInfo.runLimits.fsize)
	{
		if(SetRLimit(RLIMIT_FSIZE, runInfo.runLimits.fsize) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set file size limit to "<<runInfo.runLimits.fsize<<"."<<endlog;
			return false;
		}
	}
	if(runInfo.runLimits.stack)
	{
		if(SetRLimit(RLIMIT_STACK, runInfo.runLimits.stack) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set stack limit to "<<runInfo.runLimits.stack<<"."<<endlog;
			return false;
		}
	}
	if(runInfo.runLimits.nproc)
	{
		if(SetRLimit(RLIMIT_NPROC, runInfo.runLimits.nproc) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set nproc limit to "<<runInfo.runLimits.nproc<<"."<<endlog;
			return false;
		}
	}
	if(runInfo.runLimits.nofile)
	{
		if(SetRLimit(RLIMIT_NOFILE, runInfo.runLimits.nofile) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set file limit to "<<runInfo.runLimits.nofile<<"."<<endlog;
			return false;
		}
	}

	if(!runInfo.workdir.empty())
	{
		if(chdir(runInfo.workdir.c_str()) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to set work dir to "<<runInfo.workdir<<"."<<endlog;
			return false;
		}
	}
*/	
	//if(runInfo.bTrace)
	//{
		if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0)
		{
			log(Log::WARNING)<<"NativeRunner: Failed to trace child."<<endlog;
			return false;
		}
	//}

	sprintf(tmp, "%s/%d", runInfo.filePath.c_str(), rid);
	sprintf(tmp2, "%d", rid);

	ret = execl(tmp, tmp2, NULL);
	if(ret < 0)
	{
		log(Log::WARNING)<<"NativeRunner: Failed to execl child."<<endlog;
		return false;
	}
	return true;
}
