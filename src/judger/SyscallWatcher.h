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

class SyscallWatcher
{
public:
	void SetChildPid(int pid){this->pid = pid;}

	const char *GetSyscallName(int syscallNum)const;
	bool IsSyscallAllowed(int syscallNum, struct user_regs_struct *regs)const;

	inline bool IsValidSyscallNum(int syscallNum)const;
private:
	int pid;
};

#endif
