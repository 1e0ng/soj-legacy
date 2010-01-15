/*
 * =====================================================================================
 *
 *       Filename:  NativeSandbox.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/04/2009 04:02:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ding Wenpeng
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef NATIVESANDBOX_H
#define NATIVESANDBOX_H

#include "Sandbox.h"
#include "SyscallWatcher.h"

class NativeSandbox: public Sandbox
{
public:
	NativeSandbox();

	//usually this mean the beginning of a new child
	virtual void SetChildPid(int pid);

	virtual void Watch();//start trace the child;must be called after SetChildPid

	virtual bool IsNormalExit()const{return bNormalExit;}
	virtual bool IsRunning()const{return bRunning;}
	virtual int GetExitStatus()const{return status;}
	virtual bool IsTermByRestrictedSyscall()const{return bTermByRestrictedSyscall;}

	//virtual const RunUsage GetRunUsage()const{return ru;}
private:
	void KillChild();
	bool UpdateRunUsage();

	int pid;
	int status;
	bool bNormalExit;
	bool bRunning;
	bool bTermByRestrictedSyscall;
	//RunUsage ru;
	SyscallWatcher watcher;
};

#endif
