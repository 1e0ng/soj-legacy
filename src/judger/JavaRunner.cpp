#include "JavaRunner.h"
#include "RunStruts.h"
#include "Log.h"
#include "Judger.h"
#include "util.h"

#include <time.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/ptrace.h>

using namespace std;

void JavaRunner::SetRunInfo(const RunInfo &info)
{
    runInfo = info;
}

void JavaRunner::SetTimeLimit(long time)
{
    runInfo.runLimits.time = time;
}

void JavaRunner::SetMemoryLimit(long memory)
{
    runInfo.runLimits.memory = memory;
    runInfo.runLimits.vm = memory;// + 10 * 1024 * 1024;
}

void JavaRunner::Run(int proid, int rid, const string &lang)
{
    int p1[2];//pipe the result
    int p2[2];//pipe the runTime
    int p3[2];//pipe the runMemory
    if(pipe(p1)<0||pipe(p2)<0||pipe(p3)<0){
        log(Log::INFO)<<"JavaRunner::Run : create pipe error."<<endlog;
        result=SYS_ERROR;
        return;
    }
    
    pid = fork();
    if(pid < 0)
    {
        log(Log::WARNING)<<"JavaRunner::Run : fork failed."<<strerror(errno)<<endlog;
        result=SYS_ERROR;
        return;
    }
    if(pid > 0){//this is parent
        close(p1[1]);
        close(p2[1]);
        close(p3[1]);
        read(p1[0],&result,sizeof(result));
        read(p2[0],&ru.time,sizeof(ru.time));
        read(p3[0],&ru.memory,sizeof(ru.memory));
        close(p1[0]);
        close(p2[0]);
        close(p3[0]);
        wait(0);
        return;
    }
    else{//this is child
        close(p1[0]);
        close(p2[0]);
        close(p3[0]);
        int pid2= fork();
        if(pid2 < 0)
        {
            log(Log::WARNING)<<"JavaRunner::Run : fork2 failed."<<strerror(errno)<<endlog;
            result=SYS_ERROR;
            exit(0);
        }
        if(pid2 == 0)//this is grandson
        {
            if(!SetupChild(proid, rid, lang))
            {
                log(Log::WARNING)<<"JavaRunner::Run : Setup child failed. "<<strerror(errno)<<endlog;
                result=SYS_ERROR;
                exit(0);
            }
            exit(0);

        }
        else{
            sandbox->SetChildPid(pid2);
            sandbox->Watch();
            ru=sandbox->GetRunUsage();
        
            if(sandbox->IsNormalExit()){
                char tmp[512];
                snprintf(tmp,sizeof(tmp),"%s/%d/err",runInfo.filePath.c_str(),rid);
                //log(Log::INFO)<<tmp<<endlog;
                int fd_err = open(tmp, O_RDONLY);
                memset(tmp,0,16);
                read(fd_err,tmp,16);
                tmp[15]=0;
                //log(Log::INFO)<<tmp<<endlog;
                if(tmp[0]=='M'&&tmp[1]=='L'&&tmp[2]=='E'){
                    result = MEMORY_LIMIT_EXCEEDED;
                    log(Log::INFO)<<"JavaRunner::Run Java MLE."<<endlog;
                }
                else if(strlen(tmp)>0){
                    result = RUNTIME_ERROR;
                    log(Log::INFO)<<"JavaRunner::RUN Java RE."<<endlog;
                }
                else{
                    result = OK;
                }
                close(fd_err);
            }
            else
            {
                int status = sandbox->GetExitStatus();
                if(sandbox->IsTermByRestrictedSyscall())
                {
                    result = RESTRICTED_SYSCALL;
                }
                else if(WIFSIGNALED(status))
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
                        result = MEMORY_LIMIT_EXCEEDED;
                        log(Log::INFO)<<"JavaRunner::Run SIGKILL cause child terminated."<<endlog;
                        break;
                    case SIGTERM:
                        result = RUNTIME_ERROR;
                        log(Log::INFO)<<"JavaRunner::Run SIGTERM cause child terminated."<<endlog;
                        break;
                    case SIGXCPU://cputime limit exceed
                        result = TIME_LIMIT_EXCEEDED;
                        log(Log::INFO)<<"JavaRunner: TLE"<<endlog;
                        break;
                    case SIGXFSZ://fsize limit exceeded
                        result = OUTPUT_LIMIT_EXCEEDED;
                        log(Log::INFO)<<"JavaRunner: OLE"<<endlog;
                        break;
                    default:
                        log(Log::INFO)<<"JavaRunner::Run Unexpected signal: "<<WTERMSIG(status)<<endlog;
                    }
                }
                else
                {
                    //how do we come here?
                    result=SYS_ERROR;
                    log(Log::INFO)<<"JavaRunner::Run Unexpected exit status: "<<status<<endlog;
                }
            }
        }
        write(p1[1],&result,sizeof(result));
        write(p2[1],&ru.time,sizeof(ru.time));
        write(p3[1],&ru.memory,sizeof(ru.memory));
        close(p1[1]);
        close(p2[1]);
        close(p3[1]);
        exit(0);
    }
}

bool JavaRunner::SetupChild(int pid, int rid, const string &lang)
{
    //log(Log::INFO)<<"Seting up child..."<<endlog;
    //setup input and output
    char tmp[512];
    close(0);close(1);close(2);
    sprintf(tmp, "%s/%d", runInfo.inputPath.c_str(), pid);
    int fd_input = open(tmp, O_RDONLY);
    if(fd_input < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to open input file "<< tmp <<" ."<<endlog;
        return false;
    }
    sprintf(tmp, "%s/%d", runInfo.outputPath.c_str(), rid);
    int fd_output = open(tmp, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd_output < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to open output file "<< tmp << ". "<<endlog;
        return false;
    }
    
    int fd_err = open("/dev/null", O_RDWR);
    if(fd_err < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to open error file."<<endlog;
        return false;
    }
    int ret;
    ret = dup2(fd_input, STDIN_FILENO);
    if(ret < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to dup stdin"<<endlog;
        return false;
    }
    ret = dup2(fd_output, STDOUT_FILENO);
    if(ret < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to dup stdout"<<endlog;
        return false;
    }
    ret = dup2(fd_err, STDERR_FILENO);
    if(ret < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to dup stderr"<<endlog;
        return false;
    }

    if(runInfo.runLimits.time)
    {
        if(SetRLimit(RLIMIT_CPU, runInfo.runLimits.time/1000) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set cpu limit to "<<runInfo.runLimits.time<<"."<<endlog;
            return false;
        }
    }

    if(runInfo.runLimits.memory)
    {
        //log(Log::INFO)<<"memory limit: "<<runInfo.runLimits.memory<<endlog;
        if(SetRLimit(RLIMIT_DATA, runInfo.runLimits.memory) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set data limit to "<<runInfo.runLimits.memory<<"."<<endlog;
            return false;
        }
    }
    
    if(runInfo.runLimits.vm)
    {
        int as=runInfo.runLimits.vm+100*1024*1024;
        if(SetRLimit(RLIMIT_AS, as) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set as limit to "<<runInfo.runLimits.vm<<"."<<endlog;
            return false;
        }
    }
    if(runInfo.runLimits.fsize)
    {
        //log(Log::INFO)<<"fsize limit: "<<runInfo.runLimits.fsize<<endlog;
        if(SetRLimit(RLIMIT_FSIZE, runInfo.runLimits.fsize) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set file size limit to "<<runInfo.runLimits.fsize<<"."<<endlog;
            return false;
        }
    }

    if(runInfo.runLimits.stack)
    {
        //log(Log::INFO)<<"stack limit: "<<runInfo.runLimits.stack<<endlog;
        if(SetRLimit(RLIMIT_STACK, runInfo.runLimits.stack) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set stack limit to "<<runInfo.runLimits.stack<<"."<<endlog;
            return false;
        }
    }
    if(runInfo.runLimits.nproc)
    {
        //log(Log::INFO)<<"nproc limit: "<<runInfo.runLimits.nproc<<endlog;
        if(SetRLimit(RLIMIT_NPROC, runInfo.runLimits.nproc) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set nproc limit to "<<runInfo.runLimits.nproc<<"."<<endlog;
            return false;
        }
    }
    if(runInfo.runLimits.nofile)
    {
        //log(Log::INFO)<<"nofile limit: "<<runInfo.runLimits.nofile<<endlog;
        if(SetRLimit(RLIMIT_NOFILE, runInfo.runLimits.nofile) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set file limit to "<<runInfo.runLimits.nofile<<"."<<endlog;
            return false;
        }
    }
    if(!runInfo.workdir.empty())
    {
        //log(Log::INFO)<<"workdir limit: "<<runInfo.workdir.c_str()<<endlog;
        if(chdir(runInfo.workdir.c_str()) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to set work dir to "<<runInfo.workdir<<"."<<endlog;
            return false;
        }
    }
    
    if(runInfo.bTrace&&lang!="java")
    {
        //log(Log::INFO)<<"bTrace=true"<<endlog;
        if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0)
        {
            log(Log::WARNING)<<"JavaRunner: Failed to trace child."<<endlog;
            return false;
        }
    }
    snprintf(tmp,sizeof(tmp),"%s/%d/",runInfo.filePath.c_str(),rid);
    if(chmod(tmp,0777)){
        log(Log::WARNING)<<"chmod failed."<<endlog;
    }
    if(chdir(tmp)){
        log(Log::WARNING)<<"chdir failed."<<endlog;
    }
    if(setuid(3417)!=0){
        log(Log::WARNING)<<"setuid failed."<<endlog;
    }
    if(setresuid(3417,3417,3417)!=0){
        log(Log::WARNING)<<"setresuid failed."<<endlog;
    }
    ret= execlp("java", "java", "-client", "-Xint", "-Xfuture", "-Xincgc", "-Xss1m", "-Xms2m", "-Xmx128m", "Loader", NULL);
    if(ret < 0)
    {
        log(Log::WARNING)<<"JavaRunner: Failed to execl child."<<endlog;
        return false;
    }
    return true;
}
