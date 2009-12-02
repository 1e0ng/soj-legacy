#include "Configuration.h"
#include <string>

using namespace std;

int Configuration::Initialize()
{
	rootPath = "";
	configPath = "";
	logPathname = "soj.log";

	dbHost = "211.87.227.89";
	dbUsername = "soj";
	dbPassword = "soj-001-soj";
	dbDatabase = "soj";

	srcFilePath = "src";
	destFilePath = "dest";
	standardOutputPath = "sout";
	programOutputPath = "pout";
	programInputPath = "pin";
	programWorkDir = ".";
	sandboxEnabled = true;

	fsizeLimit = 0;
	stackLimit = 8192;
	nprocLimit = 1;
	nofileLimit = 5;
	javaTimeFactor = 5;
	javaMemoryFactor = 5;
	return 0;
}

