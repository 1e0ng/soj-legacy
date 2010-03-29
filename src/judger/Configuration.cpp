#include "Configuration.h"
#include <string>

using namespace std;

int Configuration::Initialize()
{
	rootPath = "";
	configPath = "";
	logPathname = "soj.log";

	dbHost = "localhost";
	dbUsername = "soj";
	dbPassword = "soj-001-soj";
	dbDatabase = "soj";

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

