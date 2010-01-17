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
#include <vector>
#include <string>

class Sandbox
{
public:
	virtual ~Sandbox(){}
	virtual void Watch() = 0;

	virtual void SetChildPid(int pid) = 0;
	virtual RunUsage GetRunUsage() const = 0;
	virtual bool IsNormalExit() const = 0;
	virtual bool IsRunning() const = 0;
	virtual int GetExitStatus() const = 0;
	virtual bool IsTermByRestrictedSyscall()const = 0;
	//virtual const RunUsage GetRunUsage() const = 0;
};

class SandboxFactory
{
public:
	static SandboxFactory &GetInstance()
	{
		static SandboxFactory instance;
		return instance;
	}

	int Initialize();

	Sandbox *GetSandbox(const std::string &type)const;
	void DisposeSandbox(Sandbox *sandbox){}
private:
	SandboxFactory();
	~SandboxFactory();
	SandboxFactory(const SandboxFactory &);
	SandboxFactory &operator=(const SandboxFactory &);

	std::vector<Sandbox *> sandboxes;
};

#endif
