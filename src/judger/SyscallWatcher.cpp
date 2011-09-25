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
#include "Common.h"
#include "util.h"

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>

using namespace std;

#define array_size(ar) (sizeof(ar)/(sizeof(ar[0])))
static const bool IsCallAllowed[512]={
    1, //0, restart_syscall
    1, //1, exit
    0, //2, fork
    1, //3, read
    1, //4, write
    1, //5, open
    0, //6, close
    0, //7, waitpid
    0, //8, creat
    1, //9, link
    0, //10, unlink
    0, //11, execve
    1, //12, chdir
    0, //13, time
    0, //14, mknod
    0, //15, chmod
    0, //16, lchown
    0, //17, break
    0, //18, oldstat
    0, //19, lseek
    0, //20, getpid
    0, //21, mount
    0, //22, umount
    0, //23, setuid
    0, //24, getuid
    0, //25, stime
    0, //26, ptrace
    0, //27, alarm
    0, //28, oldfstat
    0, //29, pause
    0, //30, utime
    0, //31, stty
    0, //32, gtty
    0, //33, access
    0, //34, nice
    0, //35, ftime
    0, //36, sync
    0, //37, kill
    0, //38, rename
    0, //39, mkdir
    0, //40, rmdir
    0, //41, dup
    0, //42, pipe
    0, //43, times
    0, //44, prof
    1, //45, brk
    0, //46, setgid
    0, //47, getgid
    0, //48, signal
    0, //49, geteuid
    0, //50, getegid
    0, //51, acctSYS_exit
    0, //52, umount2
    0, //53, lock
    1, //54, ioctl/////////////////////for pascal
    0, //55, fcntl
    0, //56, mpx
    0, //57, setpgid
    0, //58, ulimit
    0, //59, oldolduname
    0, //60, umask
    0, //61, chroot
    0, //62, ustat
    1, //63, dup2
    0, //64, getppid
    0, //65, getpgrp
    0, //66, setsid
    0, //67, sigaction
    0, //68, sgetmask
    0, //69, ssetmask
    0, //70, setreuid
    0, //71, setregid
    0, //72, sigsuspend
    0, //73, sigpending
    0, //74, sethostname
    0, //75, setrlimit
    0, //76, getrlimit
    0, //77, getrusage
    0, //78, gettimeofday
    0, //79, settimeofday
    0, //80, getgroups
    0, //81, setgroups
    0, //82, select
    0, //83, symlink
    0, //84, oldlstat
    1, //85, readlink////////////////////////////////////
    0, //86, uselib
    0, //87, swapon
    0, //88, reboot
    0, //89, readdir
    0, //90, mmap
    0, //91, munmap
    0, //92, truncate
    0, //93, ftruncate
    0, //94, fchmod
    0, //95, fchown
    0, //96, getpriority
    0, //97, setpriority
    0, //98, profil
    0, //99, statfs
    0, //100, fstatfs
    0, //101, ioperm
    0, //102, socketcall
    0, //103, syslog
    0, //104, setitimer
    0, //105, getitimer
    0, //106, stat
    0, //107, lstat
    0, //108, fstat
    0, //109, olduname
    0, //110, iopl
    0, //111, vhangup
    0, //112, idle
    0, //113, vm86old
    0, //114, wait4
    0, //115, swapoff
    0, //116, sysinfo
    0, //117, ipc
    0, //118, fsync
    0, //119, sigreturn
    0, //120, clone
    0, //121, setdomainname
    1, //122, uname
    0, //123, modify_ldt
    0, //124, adjtimex
    0, //125, mprotect
    0, //126, sigprocmask
    0, //127, create_module
    0, //128, init_module
    0, //129, delete_module
    0, //130, get_kernel_syms
    0, //131, quotactl
    0, //132, getpgid
    0, //133, fchdir
    0, //134, bdflush
    0, //135, sysfs
    0, //136, personality
    0, //137, afs_syscall
    0, //138, setfsuid
    0, //139, setfsgid
    0, //140, llseek
    0, //141, getdents
    0, //142, newselect
    0, //143, flock
    0, //144, msync
    0, //145, readv
    0, //146, writev
    0, //147, getsid
    0, //148, fdatasync
    0, //149, sysctl
    0, //150, mlock
    0, //151, munlock
    0, //152, mlockall
    0, //153, munlockall
    0, //154, sched_setparam
    0, //155, sched_getparam
    0, //156, sched_setscheduler
    0, //157, sched_getscheduler
    1, //158, sched_yield
    0, //159, sched_get_priority_max
    0, //160, sched_get_priority_min
    0, //161, sched_rr_get_interval
    0, //162, nanosleep
    0, //163, mremap
    0, //164, setresuid
    0, //165, getresuid
    0, //166, vm86
    0, //167, query_module
    0, //168, poll
    0, //169, nfsservctl
    0, //170, setresgid
    0, //171, getresgid
    0, //172, prctl
    0, //173, rt_sigreturn
    1, //174, rt_sigaction//////////////////////////
    0, //175, rt_sigprocmask
    0, //176, rt_sigpending
    0, //177, rt_sigtimedwait
    0, //178, rt_sigqueueinfo
    0, //179, rt_sigsuspend
    0, //180, pread64
    0, //181, pwrite64
    0, //182, chown
    0, //183, getcwd
    0, //184, capget
    0, //185, capset
    0, //186, sigaltstack
    0, //187, sendfile
    0, //188, getpmsg
    0, //189, putpmsg
    0, //190, vfork
    1, //191, ugetrlimit////////////////////////////////////
    1, //192, mmap2
    0, //193, truncate64
    0, //194, ftruncate64
    0, //195, stat64
    0, //196, lstat64
    1, //197, fstat64
    0, //198, lchown32
    0, //199, getuid32
    0, //200, getgid32
    0, //201, geteuid32
    0, //202, getegid32
    0, //203, setreuid32
    0, //204, setregid32
    0, //205, getgroups32
    0, //206, setgroups32
    0, //207, fchown32
    0, //208, setresuid32
    0, //209, getresuid32
    0, //210, setresgid32
    0, //211, getresgid32
    0, //212, chown32
    0, //213, setuid32
    0, //214, setgid32
    0, //215, setfsuid32
    0, //216, setfsgid32
    0, //217, pivot_root
    0, //218, mincore
    0, //219, madvise
    0, //220, madvise1
    0, //221, getdents64
    0, //222, fcntl64
    0, //223, unused
    0, //224, gettid
    0, //225, readahead
    0, //226, setxattr
    0, //227, lsetxattr
    0, //228, fsetxattr
    0, //229, getxattr
    0, //230, lgetxattr
    1, //231, fgetxattr
    0, //232, listxattr
    0, //233, llistxattr
    0, //234, flistxattr
    0, //235, removexattr
    0, //236, lremovexattr
    0, //237, fremovexattr
    0, //238, tkill
    0, //239, sendfile64
    0, //240, futex
    0, //241, sched_setaffinity
    0, //242, sched_getaffinity
    1, //243, set_thread_area
    0, //244, get_thread_area
    0, //245, io_setup
    0, //246, io_destroy
    0, //247, io_getevents
    0, //248, io_submit
    0, //249, io_cancel
    0, //250, fadvise64
    0, //251, unused
    1, //252, exit_group
    0, //253, lookup_dcookie
    0, //254, epoll_create
    0, //255, epoll_ctl
    0, //256, epoll_wait
    0, //257, remap_file_pages
    0, //258, set_tid_address
    0, //259, timer_create
    0, //260, timer_settime
    0, //261, timer_gettime
    0, //262, timer_getoverrun
    0, //263, timer_delete
    0, //264, clock_settime
    0, //265, clock_gettime
    0, //266, clock_getres
    0, //267, clock_nanosleep
    0, //268, statfs64
    0, //269, fstatfs64
    0, //270, tgkill
    0, //271, utimes
    0, //272, fadvise64_64
    0, //273, vserver
	0, //274, mbind
	0, //275, get_mempolicy
	0, //276, set_mempolicy
	0, //277, mq_open
	0, //278, mq_unlink
	0, //279, mq_timedsend
	0, //280, mq_timedreceive
	0, //281, mq_notify
	0, //282, mq_getsetattr
	0, //283, kexec_load
	0, //284, waitid
	0, //285, ni_syscall
	0, //286, add_key
	0, //287, request_key
	0, //288, keyctl
	0, //289, ioprio_set
	0, //290, ioprio_get
	0, //291, inotify_init
	0, //292, inotify_add_watch
	0, //293, inotify_rm_watch
	0, //294, migrate_pages
	0, //295, openat
	0, //296, mkdirat
	0, //297, mknodat
	0, //298, fchownat
	0, //299, futimesat
	0, //300, fstatat64
	0, //301, unlinkat
	0, //302, renameat
	0, //303, linkat
	0, //304, symlinkat
	0, //305, readlinkat
	0, //306, fchmodat
	0, //307, faccessat
	0, //308, pselect6
	0, //309, ppoll
	0, //310, unshare
	0, //311, set_robust_list
	0, //312, get_robust_list
	0, //313, splice
	0, //314, sync_file_range
	0, //315, tee
	0, //316, vmsplice
	0, //317, move_pages

};
/*
bool AllowedToOpen(const string& path, int flags) {
    if ((flags & O_WRONLY) == O_WRONLY ||
        (flags & O_RDWR) == O_RDWR ||
        (flags & O_CREAT) == O_CREAT ||
        (flags & O_APPEND) == O_APPEND) {
        log(Log::INFO)<<"Opening "<<path<<" with flags "<<flags<<" is not allowed";
        return false;
    }
    if (path.empty()) {
        log(Log::INFO)<<"Can not open an empty file";
        return false;
    }
    if (path[0] == '/' || path[0] == '.') {
        if (!(path.substr(0, 6) == "/proc/" || path.substr(path.length() - 3, 3) == ".so" 
				|| path.substr(path.length() - 2, 2) == ".a" || path == "/dev/urandom")) {
            log(Log::INFO)<<"Opening "<<path<<" with flags "<<flags<<" is not allowed";
            return false;
        }
    }
    return true;
}
*/
const char * SyscallWatcher::GetSyscallName(int syscallNum)const
{
	if(!IsValidSyscallNum(syscallNum))
		return NULL;
	return SyscallName[syscallNum];
}

bool SyscallWatcher::IsSyscallAllowed(int syscallNum, struct user_regs_struct *regs)const
{
	//log(Log::INFO)<<SyscallName[syscallNum]<<" called"<<endlog;	
	//static bool bEnterCall = true;
	if(IsValidSyscallNum(syscallNum))
	{
		//bEnterCall = !bEnterCall;
		/*switch(syscallNum)
		{
		case SYS_execve:
			if(bEnterCall)
			{
				//static bool bFirstExecve = true;
				//if(bFirstExecve)
				bEnterCall=false;
				return true;
				//else
				//{
				//	log(Log::INFO)<<"Syscall: Execve called."<<endlog;
				//	return false;
				//}
			}
			break;
		case SYS_open:
			if(bEnterCall)
			{
				char path[512];
				if(PeekStringFromProc(pid, regs->ebx, path, sizeof(path)) < 0)
				{
					log(Log::INFO)<<"Peek string from process "<<pid<<" failed"<<endlog;
					return true;
				}
				dlog<<"Opening file "<<path<<" with flag "<<regs->ecx<<endlog;
				return AllowedToOpen(path, regs->ecx);
			}
			break;
		
		}*/
		if(IsCallAllowed[syscallNum])return true;
	}
	log(Log::INFO)<<"\""<<SyscallName[syscallNum]<<"\""<<" is not allowed."<<endlog;
	return false;
}

bool SyscallWatcher::IsValidSyscallNum(int syscallNum)const
{
	if(syscallNum < 0 || syscallNum >334)
		return false;
	return true;
}


