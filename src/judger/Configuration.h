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
	std::string GetCompilerOutputPath()const;
	std::string GetStandardOutputPath()const;
	std::string GetProgramOutputPath()const;

	std::string GetConfigurationPath()const;
private:
	Configuration(){}
	~Configuration(){}
	Configuration(const Configuration &);
	Configuration &operator=(const Configuration &);
};

#endif
