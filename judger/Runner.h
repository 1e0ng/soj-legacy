#ifndef RUNNER_H
#define RUNNER_H

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

#endif
