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

//in a syscall, parameters are stored in ebx, ecx, edx and stack 

//peek string from process pid at address address
//the string will be as most size long if no \0 met
//return the bytes read or -1 if failed to peek data
int PeekStringFromProc(int pid, unsigned long address, char *buf, size_t size);

#endif
