#ifndef RUNNER_H
#define RUNNER_H
#include <string>
#include "RunStruts.h"

class Runner
{
public:
	enum {OK, RUNTIME_ERROR, MEMORY_LIMIT_EXCEEDED, TIME_LIMIT_EXCEEDED,
		OUTPUT_LIMIT_EXCEEDED, RESTRICTED_SYSCALL, SYS_ERROR = 42};
	virtual ~Runner(){}

	virtual void Run(int pid, int rid) = 0;//whether terminated normally
	virtual int GetResult()const = 0;
	virtual const RunUsage GetRunUsage()const  = 0;

	virtual void SetRunInfo(const RunInfo &info) = 0;
	virtual void SetTimeLimit(long time) = 0;
	virtual void SetMemoryLimit(long memory) = 0;
};

class RunnerFactory
{
public:
	static RunnerFactory &GetInstance()
	{
		static RunnerFactory instance;
		return instance;
	}

	int Initialize();

	Runner *GetRunner(const std::string &lan);
	void DisposeRunner(Runner *runner);
private:
	RunnerFactory();
	~RunnerFactory();
	RunnerFactory(const RunnerFactory &);
	RunnerFactory &operator = (const RunnerFactory &);
	RunInfo ri;
};

#endif
