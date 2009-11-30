#ifndef RUNNER_H
#define RUNNER_H
#include <string>
#include <vector>
struct RunInfo;
struct RunUsage;

class Runner
{

public:
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
private:
	RunnerFactory();
	~RunnerFactory();
	RunnerFactory(const RunnerFactory &);
	RunnerFactory &operator = (const RunnerFactory &);
	std::vector<Runner *> runners;
};

#endif
