#ifndef RUNSTRUTS_H
#define RUNSTRUTS_H

#include <string>
#include <sys/resource.h>

struct RunUsage
{
	int time;//run time in ms
	int memory;//memory usage in kilobytes
};

struct RunLimits
{
	//any field whose value is zero indicates no limit
	rlim_t time;//run time limit in ms
	rlim_t memory;//memory limit in bytes 
	rlim_t vm;//virutal memory limit in bytes
	rlim_t fsize;//output file size limit in bytes
	rlim_t stack;//stack size limit in bytes
	rlim_t nproc;//number of processes limit
	rlim_t nofile;//number of files
};

struct RunInfo
{
//information about the program to be run
	RunInfo()
		:filePath(), inputPath(), outputPath(), workdir(), bTrace(true), runLimits()
	{}
	RunInfo(const RunInfo &rhs)
		:filePath(rhs.filePath), inputPath(rhs.inputPath), outputPath(rhs.outputPath),
		workdir(rhs.workdir), bTrace(rhs.bTrace), runLimits(rhs.runLimits)
	{}
	RunInfo &operator = (const RunInfo &rhs)
	{
		filePath = rhs.filePath;
		inputPath = rhs.inputPath;
		outputPath = rhs.outputPath;
		workdir = rhs.workdir;
		bTrace = rhs.bTrace;
		runLimits = rhs.runLimits;
		return *this;
	}
	std::string filePath;
	std::string inputPath;
	std::string outputPath;
	std::string workdir;
	bool bTrace;
	RunLimits runLimits;
};

#endif
