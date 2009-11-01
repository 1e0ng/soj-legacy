#include "Common.h"
#include <cstdlib>

using namespace std;

const char *signal_name[] =
{
	"INVALID_SIGNAME",
	"SIGHUP",
	"SIGINT",
	"SIGQUIT",
	"SIGILL",
	"SIGTRAP",
	"SIGIOT",
	"SIGBUS",
	"SIGFPE",
	"SIGKILL",
	"SIGUSR1",
	"SIGSEGV",
	"SIGUSR2",
	"SIGPIPE",
	"SIGALRM",
	"SIGTERM", 
	"SIGSTKFLT",
	"SIGCHLD",
	"SIGCONT",
	"SIGSTOP",
	"SIGTSTP",
	"SIGTTIN",
	"SIGTTOU",
	"SIGURG",
	"SIGXCPU",
	"SIGXFSZ",
	"SIGVTALRM",
	"SIGPROF",
	"SIGWINCH",
	"SIGIO",
	"SIGPWR"
};

string GetTimeInString(const char *fmt)
{
	time_t t = time(NULL);
	struct tm tm;
	localtime_r(&t, &tm);
	char buf[256];
	strftime(buf, sizeof(buf), fmt, &tm);
	return buf;
}
