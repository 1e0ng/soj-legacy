#ifndef RUNSTRUTS_H
#define RUNSTRUTS_H

#include <string>
#include <sys/resource.h>

struct RunUsage
{
	rlim_t time;//run time in ms
	rlim_t memory;//memory usage in bytes
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
};

struct RunInfo
{
//information about the program to be run
	std::string pathname;
	std::string inputFilename;
	std::string outputFilename;
	std::string errFilename;
	RunLimits runLimits;
};

#endif
