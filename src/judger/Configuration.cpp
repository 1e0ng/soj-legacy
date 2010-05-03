#include "Configuration.h"
#include "../common/IniFile.h"
#include <string>

using namespace std;

int Configuration::Initialize()
{
	rootPath = "./";
	configPath = "./soj.conf";
	logPathname = "./";

	dbHost = "localhost";
	dbUsername = "soj";
	dbPassword = "soj-001-soj";
	dbDatabase = "soj";

    cCompiler = "gcc";
    cCompilerOpt = "-g -O2 -std=gnu99 -static -lm ";
    cppCompiler = "g++";
    cppCompilerOpt = "-g -O2 -std=gnu99 -static -lm ";
    javaCompiler = "javac";
    javaCompilerOpt = "-O -sourcepath . -source 1.5 ";
    javaRunner = "java";

	srcFilePath = "src";
	destFilePath = "dest";
	standardOutputPath = "sout";
	programOutputPath = "pout";
	programInputPath = "pin";
	programWorkDir = "";
	sandboxEnabled = true;

	fsizeLimit = 10*1024*1024;
	stackLimit = 2*1024*1024;
	nprocLimit = 0;
	nofileLimit = 0;
	javaTimeFactor = 5;
	javaMemoryFactor = 5;
	return 0;
}

bool Configuration::InitFromFile()
{
    IniFile ini;
    if(ini.InitFromFile(configPath.c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
