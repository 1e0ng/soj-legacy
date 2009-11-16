/*
 * =====================================================================================
 *
 *       Filename:  SyscallWatcher.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/03/2009 01:44:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ding Wenpeng
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef SYSCALLWATCHER_H
#define SYSCALLWATCHER_H

#include <vector>
#include "SyscallRule.h"

//#include <vector>

//struct user_regs_struct;

class SyscallWatcher
{
public:
	SyscallWatcher();
	~SyscallWatcher();

	void SetChildPid(int pid){this->pid = pid;}

	static const char *syscallNames[];

	const char *GetSyscallName(int syscallNum)const;
	bool IsSyscallAllowed(int syscallNum, struct user_regs_struct *regs)const;
	bool IsRestrictedSyscall(int syscallNum)const;

	int BanSyscall(int syscallNum);
	int AllowSyscall(int syscallNum);
	int SetSyscallRule(int syscallNum, SyscallRule *rule);

	inline bool IsValidSyscallNum(int syscallNum)const;
private:
	void InitRules();
	
	int pid;
	std::vector<SyscallRule *> rules;
};

#endif
