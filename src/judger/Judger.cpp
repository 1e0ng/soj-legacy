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
	if(Configuration::GetInstance().Initialize() != 0)
	{
		cerr<<"Can't initialize configuration."<<endl;
		return -1;
	}
	if(_log.Initialize() != 0)
	{
		cerr<<"Log initialization failed."<<endl;
		return -1;
	}
	if(CompilerFactory::GetInstance().Initialize() != 0)
	{
		log(Log::ERROR)<<"Compilers initialization failed."<<endlog;
		return -1;
	}
	if(RunnerFactory::GetInstance().Initialize() != 0)
	{
		log(Log::ERROR)<<"Compilers initialization failed."<<endlog;
	}
	if(theChecker.Initialize() != 0)
	{
		log(Log::ERROR)<<"FileChecker initialization failed."<<endlog;
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
	do
	{
		int rid = 1, lanid = 1;
		int i = 0;

		string lan = GetLanName(lanid);

		Compiler *compiler = CompilerFactory::GetInstance().GetCompiler(lan);
		if(!compiler->Compile(rid))
		{
			//mard ce
			cout<<"CE"<<endl;
			continue;//retry
		}
		CompilerFactory::GetInstance().DisposeCompiler(compiler);

		Runner *runner = RunnerFactory::GetInstance().GetRunner(lan);
		int result = Runner::OK;
		long timeLimit = 1000/*in ms */, memoryLimit = 64 * 1024 * 1024/* in bytes */;
		runner->SetTimeLimit(timeLimit);
		runner->SetMemoryLimit(memoryLimit);
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
			else break;
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
			switch(result)
			{
			case Runner::RUNTIME_ERROR:
			case Runner::OUTPUT_LIMIT_EXCEEDED:
			case Runner::RESTRICTED_SYSCALL:
				cout<<"RE"<<endl;
				break;
			case Runner::MEMORY_LIMIT_EXCEEDED:
				cout<<"MLE"<<endl;
				break;
			case Runner::TIME_LIMIT_EXCEEDED:
				cout<<"TLE"<<endl;
				break;
			default:
				log(Log::WARNING)<<"Unknown run result!"<<endlog;
			}
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
		switch(result)
		{
		case OutputChecker::OK:
			cout<<"AC"<<endl;
			break;
		case OutputChecker::PE:
			cout<<"PE"<<endl;
			break;
		case OutputChecker::WA:
			cout<<"WA"<<endl;
			break;
		default:
			log(Log::WARNING)<<"unknown check result."<<endlog;
		}

	}while(0);
	return 0;
}
