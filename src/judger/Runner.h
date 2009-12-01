#ifndef RUNNER_H
#define RUNNER_H
#include <string>
struct RunInfo;
struct RunUsage;

class Runner
{
public:
	enum {OK, RUNTIME_ERROR, MEMORY_LIMIT_EXCEEDED, TIME_LIMIT_EXCEEDED,
		OUTPUT_LIMIT_EXCEEDED, RESTRICTED_SYSCALL};

	virtual bool Run() = 0;//whether terminated normally
	virtual int GetResult()const = 0;
	virtual const RunUsage *GetRunUsage()const  = 0;

	virtual void SetRunInfo(const RunInfo &info) = 0;
};

class RunnerFactory
{
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
};

#endif
