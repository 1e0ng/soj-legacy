#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>
#include <sys/resource.h>

//set both soft limit and hardlimit for resource resource
//on success returns true
bool SetRLimit(int resource, rlim_t limit);

struct RunUsage;
//get the run usage of process pid and put it in ru
bool GetCurrentRunUsage(pid_t pid, RunUsage &ru);

#endif
