#include "Judger.h"
#include "util.h"
#include "Configuration.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

bool bDeamon = false;

void SigkillHandler(int)
{
	Judger::GetInstance().bStopped = true;
}

void PrintUsage()
{
    printf("Usage:\nsoj [-deamon] [-conf filepath]\n");
}

void ParseArgs(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-deamon") == 0)
        {
            bDeamon = true;
        }
        else if(strcmp(argv[i], "-conf"))
        {
            if(i + 1 < argc)
                Configuration::GetInstance().SetConfigFilePath(argv[i + 1]);
            else
            {
                PrintUsage();
                exit(0);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if(AlreadyRunning())
        exit(0);
    ParseArgs(argc, argv);
	Judger &j = Judger::GetInstance();
	if(j.StartUp() != 0)
	{
		cerr<<"Failed to start."<<endl;
		exit(0);
	}
    if(bDeamon)
        Deamonize();
	j.Run();
	j.CleanUp();
	
	return 0;
}
