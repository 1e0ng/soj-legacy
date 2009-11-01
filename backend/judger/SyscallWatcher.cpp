/*
 * =====================================================================================
 *
 *       Filename:  SyscallWatcher.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/03/2009 02:02:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ding Wenpeng
 *        Company:  
 *
 * =====================================================================================
 */
#include "SyscallWatcher.h"
#include "Log.h"

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>

using namespace std;

const char *SyscallWatcher::syscallNames[] = {
    "restart_syscall", //1
    "exit",
    "fork",
    "read",
    "write",
    "open",		//5
    "close",
    "waitpid",
    "creat",
    "link",
    "unlink",	//10
    "execve",
    "chdir",
    "time",
    "mknod",
    "chmod",	//15
    "lchown",
    "break",
    "oldstat",
    "lseek",
    "getpid",	//20
    "mount",
    "umount",
    "setuid",
    "getuid",
    "stime",	//25
    "ptrace",
    "alarm",
    "oldfstat",
    "pause",
    "utime",	//30
    "stty",
    "gtty",
    "access",
    "nice",
    "ftime",	//35
    "sync",
    "kill",
    "rename",
    "mkdir",
    "rmdir",	//40
    "dup",
    "pipe",
    "times",
    "prof",
    "brk",		//45
    "setgid",
    "getgid",
    "signal",
    "geteuid",
    "getegid",	//50
    "acct",
    "umount2",
    "lock",
    "ioctl",
    "fcntl",	//55
    "mpx",
    "setpgid",
    "ulimit",
    "oldolduname",
    "umask",	//60
    "chroot",
    "ustat",
    "dup2",
    "getppid",
    "getpgrp",	//65
    "setsid",
    "sigaction",
    "sgetmask",
    "ssetmask",
    "setreuid",	//70
    "setregid",
    "sigsuspend",
    "sigpending",
    "sethostname",
    "setrlimit", //75
    "getrlimit",
    "getrusage",
    "gettimeofday",
    "settimeofday",
    "getgroups", //80
    "setgroups",
    "select",
    "symlink",
    "oldlstat",
    "readlink",	//85
    "uselib",
    "swapon",
    "reboot",
    "readdir",
    "mmap",		//90
    "munmap",
    "truncate",
    "ftruncate",
    "fchmod",
    "fchown",	//95
    "getpriority",
    "setpriority",
    "profil",
    "statfs",
    "fstatfs",	//100
    "ioperm",
    "socketcall",
    "syslog",
    "setitimer",
    "getitimer", //105
    "stat",
    "lstat",
    "fstat",
    "olduname",
    "iopl",		//110
    "vhangup",
    "idle",
    "vm86old",
    "wait4",
    "swapoff",	//115
    "sysinfo",
    "ipc",
    "fsync",
    "sigreturn",
    "clone",	//120
    "setdomainname",
    "uname",
    "modify_ldt",
    "adjtimex",
    "mprotect",		//125
    "sigprocmask",
    "create_module",
    "init_module",
    "delete_module",
    "get_kernel_syms",//130
    "quotactl",
    "getpgid",
    "fchdir",
    "bdflush",
    "sysfs",	//135
    "personality",
    "afs_syscall",
    "setfsuid",
    "setfsgid",
    "llseek",	//140
    "getdents",
    "newselect",
    "flock",
    "msync",
    "readv",	//145
    "writev",
    "getsid",
    "fdatasync",
    "sysctl",
    "mlock",	//150
    "munlock",
    "mlockall",
    "munlockall",
    "sched_setparam",
    "sched_getparam", //155
    "sched_setscheduler",
    "sched_getscheduler",
    "sched_yield",
    "sched_get_priority_max",
    "sched_get_priority_min",//160
    "sched_rr_get_interval",
    "nanosleep",
    "mremap",
    "setresuid",
    "getresuid",	//165
    "vm86",
    "query_module",
    "poll",
    "nfsservctl",
    "setresgid",	//170
    "getresgid",
    "prctl",
    "rt_sigreturn",
    "rt_sigaction",
    "rt_sigprocmask",//175
    "rt_sigpending",
    "rt_sigtimedwait",
    "rt_sigqueueinfo",
    "rt_sigsuspend",
    "pread64",		//180
    "pwrite64",
    "chown",
    "getcwd",
    "capget",
    "capset",	//185
    "sigaltstack",
    "sendfile",
    "getpmsg",
    "putpmsg",
    "vfork",	//190
    "ugetrlimit",
    "mmap2",
    "truncate64",
    "ftruncate64",
    "stat64",	//195
    "lstat64",
    "fstat64",
    "lchown32",
    "getuid32",
    "getgid32",		//200
    "geteuid32",
    "getegid32",
    "setreuid32",
    "setregid32",
    "getgroups32",	//205
    "setgroups32",
    "fchown32",
    "setresuid32",
    "getresuid32",
    "setresgid32",	//210
    "getresgid32",
    "chown32",
    "setuid32",
    "setgid32",
    "setfsuid32",	//215
    "setfsgid32",
    "pivot_root",
    "mincore",
    "madvise",
    "madvise1",		//220
    "getdents64",
    "fcntl64",
    "unused",
    "gettid",
    "readahead",	//225
    "setxattr",
    "lsetxattr",
    "fsetxattr",
    "getxattr",
    "lgetxattr",	//230
    "fgetxattr",
    "listxattr",
    "llistxattr",
    "flistxattr",
    "removexattr",	//235
    "lremovexattr",
    "fremovexattr",
    "tkill",
    "sendfile64",
    "futex",	//240
    "sched_setaffinity",
    "sched_getaffinity",
    "set_thread_area",
    "get_thread_area",
    "io_setup",		//245
    "io_destroy",
    "io_getevents",
    "io_submit",
    "io_cancel",
    "fadvise64",	//250
    "unused",
    "exit_group",
    "lookup_dcookie",
    "epoll_create",
    "epoll_ctl",	//255
    "epoll_wait",
    "remap_file_pages",
    "set_tid_address",
    "timer_create",
    "timer_settime", //260
    "timer_gettime",
    "timer_getoverrun",
    "timer_delete",
    "clock_settime",
    "clock_gettime",	//265
    "clock_getres",
    "clock_nanosleep",
    "statfs64",
    "fstatfs64",
    "tgkill",	//270
    "utimes",
    "fadvise64_64",
    "vserver",
	"mbind",
	"get_mempolicy", //275
	"set_mempolicy",
	"mq_open",
	"mq_unlink",
	"mq_timedsend",
	"mq_timedreceive",	//280
	"mq_notify",
	"mq_getsetattr",
	"kexec_load",
	"waitid",
	"ni_syscall",	//285
	"add_key",
	"request_key",
	"keyctl",
	"ioprio_set",
	"ioprio_get",	//290
	"inotify_init",
	"inotify_add_watch",
	"inotify_rm_watch",
	"migrate_pages",
	"openat",		//295
	"mkdirat",
	"mknodat",
	"fchownat",
	"futimesat",
	"fstatat64",	//300
	"unlinkat",
	"renameat",
	"linkat",
	"symlinkat",
	"readlinkat",	//305
	"fchmodat",
	"faccessat",
	"pselect6",
	"ppoll",
	"unshare",		//310
	"set_robust_list",
	"get_robust_list",
	"splice",
	"sync_file_range",
	"tee",			//315
	"vmsplice",
	"move_pages",
	"getcpu",
	"epoll_pwait",
	"utimensat",	//320
	"signalfd", 
	"timerfd_create",
	"eventfd",
	"fallocate",
	"timerfd_settime",	//325
	"timerfd_gettime",
	"signalfd4",
	"eventfd2",
	"epoll_createl",
	"dup3",		//330
	"pipe2",
	"inotify_initl",
	"pready",
	"pwritev"	//334
};

#define array_size(ar) (sizeof(ar)/(sizeof(ar[0])))

SyscallWatcher::SyscallWatcher()
	:rules(array_size(syscallNames), (SyscallRule *)NULL)
{
	InitRules();
}

SyscallWatcher::~SyscallWatcher()
{
	for(vector<SyscallRule *>::iterator it = rules.begin(); 
			it != rules.end(); ++it)
	{
		if((*it))delete *it;
	}
}

//take care of those rules needing special process
void SyscallWatcher::InitRules()
{
	int allowed_calls[] = {
		SYS_brk, SYS_read, SYS_write, SYS_close, SYS_exit,
		SYS_exit_group, SYS_access, SYS_fstat64, SYS_fstat,SYS_mmap, 
		SYS_mmap2, SYS_mprotect, SYS_munmap, SYS_set_thread_area};
	for(size_t i = 0; i < array_size(allowed_calls); i++)
		rules[allowed_calls[i]] = new AllowedSyscallRule;

	rules[SYS_execve] = new ExecveSyscallRule;
	rules[SYS_open] = new OpenSyscallRule;
}

const char * SyscallWatcher::GetSyscallName(int syscallNum)const
{
	if(!IsValidSyscallNum(syscallNum))
		return NULL;
	return syscallNames[syscallNum];
}

bool SyscallWatcher::IsSyscallAllowed(int syscallNum, struct user_regs_struct *regs)const
{
	if(IsValidSyscallNum(syscallNum))
	{
		if(rules[syscallNum] != NULL)
			return rules[syscallNum]->IsAllowed(pid, regs);
		else
		{
			static bool bEnterCall = true;
			if(bEnterCall)
			{
				log(Log::INFO)<<"Syscall "<<syscallNum<<":"<<GetSyscallName(syscallNum)<<" denied"<<endlog;
				bEnterCall = false;
			}
			else
			{
				bEnterCall = true;
			}
		}
	}
	return true;
}

bool SyscallWatcher::IsRestrictedSyscall(int syscallNum)const
{
	if(IsValidSyscallNum(syscallNum))
	{
		if(rules[syscallNum] != NULL)
			return rules[syscallNum]->IsRestrictedSyscall();
	}
	return true;
}

bool SyscallWatcher::IsValidSyscallNum(int syscallNum)const
{
	if(syscallNum < 0 || (unsigned)syscallNum >= array_size(syscallNames))
		return false;
	return true;
}

int SyscallWatcher::BanSyscall(int syscallNum)
{
	if(IsValidSyscallNum(syscallNum))
	{
		rules[syscallNum] = NULL;
	}
	return 0;
}

int SyscallWatcher::AllowSyscall(int syscallNum)
{
	if(IsValidSyscallNum(syscallNum))
	{
		rules[syscallNum] = new AllowedSyscallRule;
	}
	return 0;
}

//rule must be newed
int SyscallWatcher::SetSyscallRule(int syscallNum, SyscallRule *rule)
{
	if(IsValidSyscallNum(syscallNum))
	{
		rules[syscallNum] = rule;
	}
	return 0;
}
