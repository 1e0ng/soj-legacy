#include "Runner.h"
#include "NativeRunner.h"

using namespace std;

RunnerFactory::RunnerFactory()
{
}

RunnerFactory::~RunnerFactory()
{
}

int RunnerFactory::Initialize()
{
	return 0;
}

Runner *RunnerFactory::GetRunner(const string &lan)
{
	if(lan == "c" || lan == "c++")
	{
		return new NativeRunner();
	}
	return NULL;
}

void RunnerFactory::DisposeRunner(Runner *runner)
{
	delete runner;
}
