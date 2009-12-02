#include "Judger.h"
#include "Configuration.h"
#include "Sandbox.h"
#include "Compiler.h"
#include "Runner.h"
#include "OutputChecker.h"
#include "Log.h"
#include "RunStruts.h"
#include "cake.h"
#include "connection.h"

#include <iostream>
#include <string>

using namespace std;

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
		cerr<<"Compilers initialization failed."<<endl;
		return -1;
	}
	if(RunnerFactory::GetInstance().Initialize() != 0)
	{
		cerr<<"Compilers initialization failed."<<endl;
	}
	if(theChecker.Initialize() != 0)
	{
		cerr<<"FileChecker initialization failed."<<endl;
		return -1;
	}
	if(conn.init() != 0)
	{
		cerr<<"Database initialization failed."<<endl;
		return -1;
	}
	return 0;
}

void Judger::CleanUp()
{
	conn.close();
}

string Judger::GetLanName(int lanid)
{
	switch(lanid)
	{
	case 1:return "c++";
	case 2:return "c";
	case 3:return "java";
	default:return "";
	}
}

#define RETRY_TIME 3
int Judger::Run()
{
	struct timespec interval;
	interval.tv_sec = 0;
	interval.tv_nsec = POLL_INTERVAL / 1000;
	do
	{
		int rid;
		int i = 0;
		Cake cake;

		if(conn.fetchCake(cake) != 0)
		{
			nanosleep(&interval, NULL);
			continue;
		}
		log(Log::INFO)<<"Begin processing run "<<cake.getRid()<<" "<<endlog;
		if(cake.storeSourceCode(Configuration::GetInstance().GetSrcFilePath().c_str()))
		{
			log(Log::ERROR)<<"Store source code "<<cake.getPid()<<" failed."<<endlog;
			cake.setJudgeStatus(CE);
			conn.updateCake(cake);
			continue;
		}

		rid = cake.getRid();
		string lan = GetLanName(cake.getLanguage());

		Compiler *compiler = CompilerFactory::GetInstance().GetCompiler(lan);
		if(!compiler->Compile(rid))
		{
			//mark ce
			cake.setJudgeStatus(CE);
			conn.updateCake(cake);
			CompilerFactory::GetInstance().DisposeCompiler(compiler);
			continue;
		}
		CompilerFactory::GetInstance().DisposeCompiler(compiler);

		Runner *runner = RunnerFactory::GetInstance().GetRunner(lan);
		int result = Runner::OK;
		long timeLimit = cake.getTimeLimit()/*in ms */, memoryLimit = cake.getMemoryLimit() * 1024/* in bytes */;
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
			cake.setJudgeStatus(RE);
			conn.updateCake(cake);
			RunnerFactory::GetInstance().DisposeRunner(runner);
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
				cake.setJudgeStatus(RE);
				break;
			case Runner::MEMORY_LIMIT_EXCEEDED:
				cake.setJudgeStatus(MLE);
				break;
			case Runner::TIME_LIMIT_EXCEEDED:
				cake.setJudgeStatus(TLE);
				break;
			default:
				log(Log::WARNING)<<"Unknown run result!"<<endlog;
			}
			conn.updateCake(cake);
			RunnerFactory::GetInstance().DisposeRunner(runner);
			continue;
		}
		RunUsage ru = *runner->GetRunUsage();
		RunnerFactory::GetInstance().DisposeRunner(runner);

		result = theChecker.Check(rid);
		if(result == OutputChecker::FILE_ERROR)
		{
			log(Log::ERROR)<<"Can't check output "<<rid<<" .Skip."<<endlog;
			cake.setJudgeStatus(WA);
			conn.updateCake(cake);
			continue;
		}
		//mark this run as AC, WA, PE
		switch(result)
		{
		case OutputChecker::OK:
			cake.setJudgeStatus(AC);
			break;
		case OutputChecker::PE:
			cake.setJudgeStatus(PE);
			break;
		case OutputChecker::WA:
			cake.setJudgeStatus(WA);
			break;
		default:
			log(Log::WARNING)<<"unknown check result."<<endlog;
		}
		conn.updateCake(cake);

		log(Log::INFO)<<"Finished processing run "<<rid<<endlog;

	}while(0);
	return 0;
}
