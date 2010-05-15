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

    void SetConfigFilePath(const std::string &path)
    {
        configPath = path;
    }

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
    //compiler related
    std::string GetCCompiler()const
    {
        return cCompiler;
    }
    std::string GetCCompilerOpt()const
    {
        return cCompilerOpt;
    }
    std::string GetCppCompiler()const
    {
        return cppCompiler;
    }
    std::string GetCppCompilerOpt()const
    {
        return cppCompilerOpt;
    }
    std::string GetJavaCompiler()const
    {
        return javaCompiler;
    }
    std::string GetJavaCompilerOpt()const
    {
        return javaCompilerOpt;
    }
    std::string GetJavaRunner()const
    {
        return javaRunner;
    }

    //runtime related
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

    std::string GetServerIp()const
    {
        return serverIp;
    }
    int GetServerPort()const
    {
        return serverPort;
    }
private:
	Configuration(){}
	~Configuration(){}
	Configuration(const Configuration &);
	Configuration &operator=(const Configuration &);

    bool InitFromFile();

	std::string rootPath;
	std::string configPath;
	std::string logPathname;

    std::string cCompiler;
    std::string cCompilerOpt;
    std::string cppCompiler;
    std::string cppCompilerOpt;
    std::string javaCompiler;
    std::string javaCompilerOpt;
    std::string javaRunner;

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

    std::string serverIp;
    int serverPort;
};

#endif
