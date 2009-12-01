#include "Judger.h"
#include "Configuration.h"
#include "Sandbox.h"
#include "Compiler.h"
#include "Runner.h"
#include "OutputChecker.h"
#include "Log.h"
#include "RunStruts.h"

#include <iostream>
#include <string>

using namespace std;

bool Judger::bStopped = false;

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
		cerr<<"Compilers initialization failed."<<endl;
		return -1;
	}
	if(!theChecker.Initialize())
	{
		cerr<<"FileChecker initialization failed."<<endl;
		return -1;
	}
	return 0;
}

void Judger::CleanUp()
{
	
}

string Judger::GetLanName(int lanid)
{
	switch(lanid)
	{
	case 1:return "c";
	case 2:return "c++";
	case 3:return "java";
	default:return "";
	}
}

#define RETRY_TIME 3
int Judger::Run()
{
	while(!bStopped)
	{
		int rid = 1, lanid = 1;
		int i = 0;

		string lan = GetLanName(lanid);

		Compiler *compiler = CompilerFactory::GetInstance().GetCompiler(lan);
		for(i = 0; i < RETRY_TIME; i++)
		{
			if(!compiler->Compile(rid))
			{
				log(Log::WARNING)<<"Failed to compile "<<rid<<" .Retry."<<endlog;
				continue;//retry
			}
		}
		CompilerFactory::GetInstance().DisposeCompiler(compiler);
		if(i == RETRY_TIME)
		{
			log(Log::ERROR)<<"Can't compile source file "<<rid<<".Skip."<<endlog;
			//add skip-this-run code here
			continue;
		}

		Runner *runner = RunnerFactory::GetInstance().GetRunner(lan);
		int result = Runner::OK;
		for(i = 0; i < RETRY_TIME; i++)
		{
			if(!runner->Run(rid))
			{
				result = runner->GetResult();
				if(result == Runner::SYS_ERROR)
				{
					log(Log::WARNING)<<"Failed to run program "<<rid<<" .Retry."<<endlog;
					continue;//system error.retry
				}
				else
				{
					break;
				}
			}
		}
		if(i == RETRY_TIME)
		{
			log(Log::ERROR)<<"Can't run program "<<rid<<". Skip."<<endlog;
			//add skip-run-this code here
			continue;
		}
		else if(result != Runner::OK)
		{
			//mark this run as re, tle, mle or etc here
			continue;
		}
		RunUsage ru = *runner->GetRunUsage();
		RunnerFactory::GetInstance().DisposeRunner(runner);

		result = theChecker.Check(rid);
		if(result == OutputChecker::FILE_ERROR)
		{
			log(Log::ERROR)<<"Can't check output "<<rid<<" .Skip."<<endlog;
			continue;
		}
		//mark this run as AC, WA, PE
	}
	return 0;
}
