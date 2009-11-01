#include "Common.h"
#include "NativeSandbox.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/ptrace.h>

using namespace std;

int setup_judgee()
{
	ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	return 0;
}

pid_t fork_judgee(const char *judgee_name)
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		setup_judgee();
		execl(judgee_name, "judgee", NULL);
		exit(0);
	}
	return pid;
}

int main(int argc, char *argv[])
{
	const char* child_name = "testee";
	pid_t pid;

	pid = fork_judgee(child_name);
	if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	NativeSandbox sandbox;
	sandbox.SetChildPid(pid);
	sandbox.Start();
	
	return 0;
}
