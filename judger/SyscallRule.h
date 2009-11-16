#ifndef SYSCALLRULE_H
#define SYSCALLRULE_H

#include "Log.h"
#include <string>

struct user_regs_struct;
//the rule for each syscall
class SyscallRule
{
public:
	SyscallRule(){syscallName = NULL;bEnterCall = false;}
	virtual bool IsAllowed(int pid, struct user_regs_struct *regs) = 0;
	virtual bool IsRestrictedSyscall()const = 0;
	virtual void SetSyscallNum(int num){syscallNum = num;} 
	virtual void SetSyscallName(const char *name){syscallName = name;}
protected:
	int syscallNum;
	const char *syscallName;
	bool bEnterCall;//each syscall will cause IsAllowed executing twice
};

class BannedSyscallRule: public SyscallRule
{
public:
	virtual bool IsAllowed(int pid, struct user_regs_struct *regs)
	{
		if(bEnterCall)
		{
			dlog<<"Syscall "<<syscallNum<<":"<<syscallName<<" denied"<<endlog;
			bEnterCall = false;
		}
		else
		{
			bEnterCall = true;
		}
		return false;
	}
	virtual bool IsRestrictedSyscall()const
	{
		return true;
	}
};

class AllowedSyscallRule: public SyscallRule
{
public:
	virtual bool IsAllowed(int pid, struct user_regs_struct *regs)
	{
		return true;
	}
	virtual bool IsRestrictedSyscall()const
	{
		return false;
	}
};

class ExecveSyscallRule: public SyscallRule
{
public:
	ExecveSyscallRule(){bFirstCalled = true;}
	virtual bool IsAllowed(int pid, struct user_regs_struct *regs);
	//execve called by system once (to start the program) but can never called by user
	//so it is restricted
	virtual bool IsRestrictedSyscall()const{return true;}
private:
	bool bFirstCalled;//whether the execve call is called the first time
};

class OpenSyscallRule: public SyscallRule
{
public:
	virtual bool IsAllowed(int pid, struct user_regs_struct *regs);
	virtual bool IsRestrictedSyscall()const{return true;}
private:
	std::string GetFlagsInString(int flags);
};

#endif
