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
#include "util.h"

#include <iostream>
#include <string>
#include <cstdlib>

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
		cerr<<"Runner initialization failed."<<endl;
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

#define RETRY_TIME 3
int Judger::Run()
{
	struct timespec interval;
	interval.tv_sec = 0;
	interval.tv_nsec = POLL_INTERVAL * 1000;
	//log(Log::INFO)<<"tv_nsec:"<<interval.tv_nsec<<endlog;
	while(!bStopped)	
	{
		int rid, pid;
		int i = 0;
		Cake cake;

		if(conn.fetchCake(cake) != 0)
		{
		    sleep(1);
			//nanosleep(&interval, NULL);
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
		pid = cake.getPid();
		string lan = GetLanName(cake.getLanguage());

		Compiler *compiler = CompilerFactory::GetInstance().GetCompiler(lan);
		//log(Log::INFO)<<"The compiler name:"<<compiler->GetName()<<endlog;
		
		if(!compiler->Compile(rid))
		{
			//mark ce
			cake.setJudgeStatus(CE);
			conn.updateCake(cake);
			CompilerFactory::GetInstance().DisposeCompiler(compiler);
			log(Log::INFO)<<"Run "<<rid<<": compilation error."<<endlog;
			continue;
		}
		CompilerFactory::GetInstance().DisposeCompiler(compiler);

		Runner *runner = RunnerFactory::GetInstance().GetRunner(lan);

		int result = Runner::OK;
		long timeLimit = cake.getTimeLimit()/*in ms */, memoryLimit = cake.getMemoryLimit() * 1024/* in bytes */;
		if(lan=="java"){
			timeLimit*=Configuration::GetInstance().GetJavaTimeFactor();//Up the limit if Java is used.
			memoryLimit*=Configuration::GetInstance().GetJavaMemoryFactor();
			
		}
		runner->SetTimeLimit(timeLimit);
		runner->SetMemoryLimit(memoryLimit);
		for(i = 0; i < RETRY_TIME; i++)
		{
			runner->Run(pid,rid,lan);
			result = runner->GetResult();
			if(result==Runner::SYS_ERROR){
					log(Log::WARNING)<<"Fail to run program "<<rid<<" .Retry."<<endlog;
			}
			else{
				break;
			}
		}
		if(i == RETRY_TIME)
		{
			log(Log::ERROR)<<"Can't run program "<<rid<<". Skip."<<endlog;
			cake.setJudgeStatus(RE);
			conn.updateCake(cake);
			RunnerFactory::GetInstance().DisposeRunner(runner);
			log(Log::INFO)<<"Run "<<rid<<": runtime error."<<endlog;
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
				log(Log::INFO)<<"Run "<<rid<<": RE."<<endlog;
				break;
			case Runner::MEMORY_LIMIT_EXCEEDED:
				cake.setJudgeStatus(MLE);
				log(Log::INFO)<<"Run "<<rid<<": MLE."<<endlog;
				break;
			case Runner::TIME_LIMIT_EXCEEDED:
				cake.setJudgeStatus(TLE);
				log(Log::INFO)<<"Run "<<rid<<": TLE."<<endlog;
				break;
			default:
				cake.setJudgeStatus(RE);
				log(Log::WARNING)<<"Unknown run result!"<<endlog;
			}
			conn.updateCake(cake);
			RunnerFactory::GetInstance().DisposeRunner(runner);
			
			continue;
		}
		RunUsage ru = runner->GetRunUsage();
		RunnerFactory::GetInstance().DisposeRunner(runner);

		result = theChecker.Check(pid, rid);
		if(result == OutputChecker::FILE_ERROR)
		{
			log(Log::ERROR)<<"Can't check output "<<rid<<" .Skip."<<endlog;
			cake.setJudgeStatus(WA);
			conn.updateCake(cake);
			log(Log::INFO)<<"Run "<<rid<<": WA."<<endlog;
			continue;
		}
		//mark this run as AC, WA, PE
		cake.setRtime(ru.time);
		cake.setRmemory(ru.memory);
		switch(result)
		{
		case OutputChecker::OK:
			cake.setJudgeStatus(AC);
			log(Log::INFO)<<"Run "<<rid<<": AC."<<endlog;
			break;
		case OutputChecker::PE:
			cake.setJudgeStatus(PE);
			log(Log::INFO)<<"Run "<<rid<<": PE."<<endlog;
			break;
		case OutputChecker::WA:
			cake.setJudgeStatus(WA);
			log(Log::INFO)<<"Run "<<rid<<": WA."<<endlog;
			break;
		default:
			log(Log::WARNING)<<"unknown check result."<<endlog;
		}
		conn.updateCake(cake);
		log(Log::INFO)<<"Finish processing run "<<rid<<endlog;
	}
	return 0;
}
