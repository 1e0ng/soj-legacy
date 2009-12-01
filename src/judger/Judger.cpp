#include "Judger.h"
#include "Configuration.h"
#include "Sandbox.h"
#include "Compiler.h"
#include "Runner.h"
#include "OutputChecker.h"
#include "Log.h"

#include <iostream>

using namespace std;

int Judger::StartUp()
{
	if(!Configuration::GetInstance().Initialize())
	{
		cerr<<"Can't initialize configuration."<<endl;
		return -1;
	}
	if(!_log.Initialize())
	{
		cerr<<"Log initialization failed."<<endl;
		return -1;
	}
	if(!CompilerFactory::GetInstance().Initialize())
	{
		cerr<<"Compilers initialization failed.";
		return -1;
	}
	return 0;
}

void Judger::CleanUp()
{

}

int Judger::Run()
{
	return 0;
}
