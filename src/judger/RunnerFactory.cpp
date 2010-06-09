#include "Runner.h"
#include "NativeRunner.h"
#include "JavaRunner.h"
#include "Configuration.h"

using namespace std;

RunnerFactory::RunnerFactory()
{
}

RunnerFactory::~RunnerFactory()
{
}

int RunnerFactory::Initialize()
{
	Configuration &conf = Configuration::GetInstance();
	ri.filePath = conf.GetDestFilePath();
	ri.inputPath = conf.GetProgramInputPath();
	ri.outputPath = conf.GetProgramOutputPath();
	ri.bTrace = conf.IsSandboxEnabled();
	ri.runLimits.fsize = conf.GetFsizeLimit() * 1024 * 1024;
	ri.runLimits.nofile = conf.GetNofileLimit();
	ri.runLimits.nproc = conf.GetNprocLimit();
	ri.runLimits.stack = conf.GetStackLimit() * 1024 * 1024;
	return 0;
}

Runner *RunnerFactory::GetRunner(const string &lan){
	if(lan == "c" || lan == "c++" || lan=="pascal"){
		Runner *r = new NativeRunner();
		r->SetRunInfo(ri);
		return r;
	}
	else if(lan=="java"){
		Runner *r = new JavaRunner();
		r->SetRunInfo(ri);
		return r;
	}
	return NULL;
}

void RunnerFactory::DisposeRunner(Runner *runner){
	delete runner;
}
