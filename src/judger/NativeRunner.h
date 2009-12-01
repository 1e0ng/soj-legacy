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
	~NativeRunner(){SandboxFactory::GetInstance().DisposeSandbox(sandbox);sandbox = NULL;}

	virtual bool Run();
	virtual int GetResult()const{return result;}
	virtual const RunUsage *GetRunUsage()const{return sandbox->GetRunUsage();}

	virtual void SetRunInfo(const RunInfo &info);
private:
	bool SetupChild();

	Sandbox *sandbox;
	RunInfo runInfo;
	int result;
	pid_t pid;	
};


#endif 
