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
	sandboxEnabled = false;

	fsizeLimit = 0;
	stackLimit = 8192;
	nprocLimit = 0;
	nofileLimit = 20;
	javaTimeFactor = 5;
	javaMemoryFactor = 5;
	return 0;
}

