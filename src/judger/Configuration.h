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

	std::string GetSrcFilePath()const;
	std::string GetDestFilePath()const;
	std::string GetStandardOutputPath()const;
	std::string GetProgramOutputPath()const;
	std::string GetProgramInputPath()const;
	std::string GetProgramWorkDir()const;
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

	std::string GetConfigurationPath()const;
private:
	Configuration(){}
	~Configuration(){}
	Configuration(const Configuration &);
	Configuration &operator=(const Configuration &);

	std::string rootPath;
	std::string configPath;
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
