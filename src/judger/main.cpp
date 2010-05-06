#include "Judger.h"
#include "util.h"
#include "Configuration.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

bool bDaemon = false;
bool bSingleton = false;

void SigkillHandler(int)
{
	Judger::GetInstance().bStopped = true;
}

void PrintUsage()
{
    printf("Usage:\nsoj [-deamon] [-conf filepath] [-single]\n");
}

void ParseArgs(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-deamon") == 0)
        {
            bDaemon = true;
        }
        else if(strcmp(argv[i], "-conf") == 0)
        {
            if(i + 1 < argc)
                Configuration::GetInstance().SetConfigFilePath(argv[i + 1]);
            else
            {
                PrintUsage();
                exit(0);
            }
        }
        else if(strcmp(argv[i], "-single") == 0)
        {
            bSingleton = true;
        }
        else
        {
            PrintUsage();
            exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    ParseArgs(argc, argv);
    if( bSingleton )
    {
        int ret = AlreadyRunning();
        if(ret == 1)
            cerr<<"Another instance is running!"<<endl;
        exit(0);
    }
	Judger &j = Judger::GetInstance();
	if(j.StartUp() < 0)
	{
		cerr<<"Failed to start."<<endl;
		exit(0);
	}
    if(bDaemon)
    {
        if(Daemonize() != 0)
        {
            cerr<<"Daemonize failed!\n"<<endl;
            exit(0);
        }
    }
	j.Run();
	j.CleanUp();
	
	return 0;
}
