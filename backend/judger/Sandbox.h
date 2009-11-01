/*
 * =====================================================================================
 *
 *       Filename:  Sandbox.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/04/2009 03:54:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ding Wenpeng 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef SANDBOX_H
#define SANDBOX_H

#include "RunStruts.h"

class Sandbox
{
public:
	virtual void Start() = 0;

	virtual void SetChildPid(int pid) = 0;

	virtual bool IsNormalExit() const = 0;
	virtual bool IsRunning() const = 0;
	virtual int GetExitStatus() const = 0;
	virtual bool IsTermByRestrictedSyscall()const = 0;
	virtual const RunUsage *GetRunUsage() const = 0;
};

#endif
