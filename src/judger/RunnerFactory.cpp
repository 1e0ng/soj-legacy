#include "Runner.h"
#include "NativeRunner.h"
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
	ri.runLimits.fsize = conf.GetFsizeLimit();
	ri.runLimits.nofile = conf.GetNofileLimit();
	ri.runLimits.nproc = conf.GetNprocLimit();
	ri.runLimits.stack = conf.GetStackLimit();
	return 0;
}

Runner *RunnerFactory::GetRunner(const string &lan)
{
	//if(lan == "c" || lan == "c++")
	//{
		Runner *r = new NativeRunner();
		r->SetRunInfo(ri);
		return r;
	//}
	//return NULL;
}

void RunnerFactory::DisposeRunner(Runner *runner)
{
	delete runner;
}
