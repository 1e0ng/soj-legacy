#include "Judger.h"
#include <signal.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void SigkillHandler(int)
{
	Judger::bStopped = true;
}

int main(int argc, char *argv[])
{
	signal(SIGKILL, SigkillHandler);

	if(Judger::StartUp() != 0)
	{
		cerr<<"Failed to start."<<endl;
		exit(0);
	}
	Judger::Run();
	Judger::CleanUp();
	
	return 0;
}
