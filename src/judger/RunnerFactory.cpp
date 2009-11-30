#include "Runner.h"
#include "NativeRunner.h"

using namespace std;

RunnerFactory::RunnerFactory()
{
	runners.push_back(new NativeRunner());
}

RunnerFactory::~RunnerFactory()
{
	for(size_t i = 0; i < runners.size(); i++)
		delete runners[i];
	runners.clear();
}

int RunnerFactory::Initialize()
{
	return 0;
}

Runner *RunnerFactory::GetRunner(const string &lan)
{
	if(lan == "c" || lan == "c++")
		return runners[0];
	return NULL;
}
