#ifndef NATIVE_RUNNER_H
#define NATIVE_RUNNER_H

#include "Runner.h"
#include "RunStruts.h"
#include "Sandbox.h"
#include "NativeSandbox.h"
#include <unistd.h>

class NativeRunner :public Runner
{
public:
	NativeRunner(){sandbox = SandboxFactory::GetInstance().GetSandbox("native");}
	virtual ~NativeRunner(){SandboxFactory::GetInstance().DisposeSandbox(sandbox);sandbox = NULL;}

	virtual void Run(int pid, int rid);
	virtual int GetResult()const{return result;}
	virtual const RunUsage GetRunUsage()const{return ru;}

	virtual void SetRunInfo(const RunInfo &info);
	virtual void SetTimeLimit(long time);
	virtual void SetMemoryLimit(long memory);
private:
	bool SetupChild(int pid, int rid);

	Sandbox *sandbox;
	RunInfo runInfo;
	int result;
	pid_t pid;	
	RunUsage ru;
};


#endif 
