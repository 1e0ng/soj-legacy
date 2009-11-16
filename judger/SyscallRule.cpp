#include "SyscallRule.h"

#include <cstdio>
#include <cstring>
#include <sstream>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h>

using namespace std;

//in a syscall, parameters are stored in ebx, ecx, edx and stack 

//peek string from process pid at address address
//the string will be as most size long if no \0 met
//return the bytes read or -1 if failed to peek data
int PeekStringFromProc(int pid, unsigned long address, char *buf, size_t size)
{
	long mask = -1<<2;//we use long as a word
	long data = 0;
	size_t i = 0;

	if(address & mask)
	{
		int base = address & mask;
		int offset = address & ~mask;
		data = ptrace(PTRACE_PEEKDATA, pid, base, 0);
		if(data < 0)
			return -1;
		for(i = 0; i < size && (offset + i < sizeof(long)) ; i++)
		{
			buf[i] = ((char *)&data)[offset + i];
			if(buf[i] == '\0')
				goto done;
		}
		address = base + ~mask + 1;
	}
	for(; i < size; address += sizeof(long))
	{
		data = ptrace(PTRACE_PEEKDATA, pid, address, 0);
		if(data < 0)
			return -1;
		for(size_t j = 0; j < sizeof(long) && i < size; j++, i++)
		{
			buf[i] = ((char *)&data)[j];
			if(buf[i] == '\0')
				goto done;
		}
	}
done:
	buf[size] = '\0';
	return i; 
}

bool ExecveSyscallRule::IsAllowed(int pid, struct user_regs_struct *regs)
{
	if(bFirstCalled)
	{
		bFirstCalled = false;
		return true;
	}
	else
	{
		char buf[1000] = {0};
		int ret = PeekStringFromProc(pid, regs->ebx, buf, sizeof(buf));
		if(ret < 0)
			log(Log::WARNING)<<"ExecveSyscallRule::IsAllowed: Peek pathname from child failed. "<<strerror(errno)<<endlog;
		log(Log::INFO)<<"execve called and target is "<<buf<<endlog;
		return false;
	}
}

#define MAX_PATH 256

bool OpenSyscallRule::IsAllowed(int pid, struct user_regs_struct *regs)
{
	char buf[MAX_PATH] = {0};//pathname for SYS_open
	int flags = regs->ecx;//flags for SYS_open
	int ret;

	ret = PeekStringFromProc(pid, regs->ebx, buf, sizeof(buf));
	if(ret < 0)
			dlog<<"OpenSyscallRule::IsAllowed: Peek pathname from child failed. "<<strerror(errno)<<endlog;

	dlog<<"Opening file \""<<buf<<"\" with flags "<<GetFlagsInString(flags)<<endlog;

	return true;
}

string OpenSyscallRule::GetFlagsInString(int flags)
{
	stringstream ss;
	
	if((flags & O_WRONLY) == O_WRONLY)
		ss<<"O_WRONLY|";
	else if((flags & O_RDWR) == O_RDWR)
		ss<<"O_RDWR|";
	else//if((flags & O_RDONLY) == O_RDONLY)
		ss<<"O_RDONLY|";
	if((flags & O_APPEND) == O_APPEND)
		ss<<"O_APPEND|";
	if((flags & O_ASYNC) == O_ASYNC)
		ss<<"O_ASYNC|";
	if((flags & O_CLOEXEC) == O_CLOEXEC)
		ss<<"O_CLOEXEC|";
	if((flags & O_CREAT) == O_CREAT)
		ss<<"O_CREAT|";
	if((flags & O_DIRECT) == O_DIRECT)
		ss<<"O_DIRECT|";
	if((flags & O_DIRECTORY) == O_DIRECTORY)
		ss<<"O_DIRECTORY|";
	if((flags & O_EXCL) == O_EXCL)
		ss<<"O_EXCL|";
	if((flags & O_NOATIME) == O_NOATIME)
		ss<<"O_NOATIME|";
	if((flags & O_NOCTTY) == O_NOCTTY)
		ss<<"O_NOCTTY|";
	if((flags & O_NOFOLLOW) == O_NOFOLLOW)
		ss<<"O_NOFOLLOW|";
	if((flags & O_NONBLOCK) == O_NONBLOCK)
		ss<<"O_NOBLOCK|";
	if((flags & O_SYNC) == O_SYNC)
		ss<<"O_SYNC|";
	if((flags & O_TRUNC) == O_TRUNC)
		ss<<"O_TRUNC|";
	return ss.str();
}
