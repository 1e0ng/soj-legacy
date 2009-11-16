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
	void SetChildPid(int pid);

	void Start();//start trace the child;must be called after SetChildPid

	bool IsNormalExit()const{return bNormalExit;}
	bool IsRunning()const{return bRunning;}
	int GetExitStatus()const{return status;}
	bool IsTermByRestrictedSyscall()const{return bTermByRestrictedSyscall;}

	const RunUsage *GetRunUsage()const{return &ru;}
private:
	void KillChild();
	bool UpdateRunUsage();

	int pid;
	int status;
	bool bNormalExit;
	bool bRunning;
	bool bTermByRestrictedSyscall;
	RunUsage ru;
	SyscallWatcher watcher;
};

#endif
