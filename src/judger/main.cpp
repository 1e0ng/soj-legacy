#include "Judger.h"
#include "util.h"
#include <signal.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void SigkillHandler(int)
{
	Judger::GetInstance().bStopped = true;
}

int main(int argc, char *argv[])
{
	InstallSignalHandler(SIGKILL, SigkillHandler);

	Judger &j = Judger::GetInstance();
	if(j.StartUp() != 0)
	{
		cerr<<"Failed to start."<<endl;
		exit(0);
	}
	j.Run();
	j.CleanUp();
	
	return 0;
}
