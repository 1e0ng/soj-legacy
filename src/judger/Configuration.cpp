#include "Configuration.h"
#include <string>

using namespace std;

int Configuration::Initialize()
{
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

string Configuration::GetSrcFilePath()const
{
	return srcFilePath;
}

string Configuration::GetDestFilePath()const
{
	return destFilePath;
}

string Configuration::GetStandardOutputPath()const
{
	return standardOutputPath;
}

string Configuration::GetProgramOutputPath()const
{
	return programOutputPath;
}

string Configuration::GetProgramInputPath()const
{
	return programInputPath;
}

string Configuration::GetProgramWorkDir()const
{
	return programWorkDir;
}
