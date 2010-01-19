#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

class Configuration
{
public:
	static Configuration &GetInstance()
	{
		static Configuration instance;
		return instance;
	}

	int Initialize();

	std::string GetRootPath()const
	{
		return rootPath;
	}
	std::string GetConfigurationPath()const
	{
		return configPath;
	}
	std::string GetLogPathname()const
	{
		return logPathname;
	}

	std::string GetDbHost()const
	{
		return dbHost;
	}
	std::string GetDbUsername()const
	{
		return dbUsername;
	}
	std::string GetDbPassword()const
	{
		return dbPassword;
	}
	std::string GetDbDatabase()const
	{
		return dbDatabase;
	}

	std::string GetSrcFilePath()const
	{
		return srcFilePath;
	}
	std::string GetDestFilePath()const
	{
		return destFilePath;
	}
	std::string GetStandardOutputPath()const
	{
		return standardOutputPath;
	}
	std::string GetProgramOutputPath()const
	{
		return programOutputPath;
	}
	std::string GetProgramInputPath()const
	{
		return programInputPath;
	}
	std::string GetProgramWorkDir()const
	{
		return programWorkDir;
	}
	bool IsSandboxEnabled()const
	{
		return sandboxEnabled;
	}
	long GetFsizeLimit()const
	{
		return fsizeLimit;
	}
	long GetStackLimit()const
	{
		return stackLimit;
	}
	long GetNprocLimit()const
	{
		return nprocLimit;
	}
	long GetNofileLimit()const
	{
		return nofileLimit;
	}
	long GetJavaTimeFactor()const
	{
		return javaTimeFactor;
	}
	long GetJavaMemoryFactor()const
	{
		return javaMemoryFactor;
	}
private:
	Configuration(){}
	~Configuration(){}
	Configuration(const Configuration &);
	Configuration &operator=(const Configuration &);

	std::string rootPath;
	std::string configPath;
	std::string logPathname;

	std::string dbHost;
	std::string dbUsername;
	std::string dbPassword;
	std::string dbDatabase;

	std::string srcFilePath;
	std::string destFilePath;
	std::string standardOutputPath;
	std::string programOutputPath;
	std::string programInputPath;
	std::string programWorkDir;

	bool sandboxEnabled;

	long fsizeLimit;
	long stackLimit;
	long nprocLimit;
	long nofileLimit;
	long javaTimeFactor;
	long javaMemoryFactor;
};

#endif
