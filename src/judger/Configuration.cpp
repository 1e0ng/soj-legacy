#include "Configuration.h"
#include "../common/IniFile.h"
#include <string>
#include <iostream>

using namespace std;

int Configuration::Initialize()
{
    if(configPath.empty())
    {
        configPath = "./judger.conf";
    }
    return InitFromFile()? 0: -1;
}

bool Configuration::InitFromFile()
{
    IniFile ini;
    char buf[512];
    if(ini.InitFromFile(configPath.c_str()))
    {
        if(!ini.GetStringValue("Judger", "RootPath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::RootPath failed!"<<endl;
            return false;
        }
        rootPath = buf;

        if(!ini.GetStringValue("Judger", "LogPath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::LogPath failed!"<<endl;
            return false;
        }
        logPathname = buf;

        if(!ini.GetStringValue("Judger", "CCompiler", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::CCompiler failed!"<<endl;
            return false;
        }
        cCompiler = buf;

        if(!ini.GetStringValue("Judger", "CCompilerOption", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::CCompilerOption failed!"<<endl;
            return false;
        }
        cCompilerOpt = buf;

        if(!ini.GetStringValue("Judger", "CppCompiler", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::CppCompiler failed!"<<endl;
            return false;
        }
        cppCompiler = buf;

        if(!ini.GetStringValue("Judger", "CppCompilerOption", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::CppCompilerOption failed!"<<endl;
            return false;
        }
        cppCompilerOpt = buf;

        if(!ini.GetStringValue("Judger", "JavaCompiler", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::JavaCompiler failed!"<<endl;
            return false;
        }
        javaCompiler = buf;

        if(!ini.GetStringValue("Judger", "JavaCompilerOption", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::JavaCompilerOption failed!"<<endl;
            return false;
        }
        javaCompilerOpt = buf;

        if(!ini.GetStringValue("Judger", "JavaRunner", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::JavaRunner failed!"<<endl;
            return false;
        }
        javaRunner = buf;

        if(!ini.GetStringValue("Judger", "PascalCompiler", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::PascalCompiler failed!"<<endl;
            return false;
        }
        pascalCompiler = buf;

        if(!ini.GetStringValue("Judger", "SourceFilePath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::SourceFilePath failed!"<<endl;
            return false;
        }
        srcFilePath = buf;

        if(!ini.GetStringValue("Judger", "DestFilePath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::DestFilePath failed!"<<endl;
            return false;
        }
        destFilePath = buf;

        if(!ini.GetStringValue("Judger", "StandardOutputPath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::StandardOutputPath failed!"<<endl;
            return false;
        }
        standardOutputPath = buf;


        if(!ini.GetStringValue("Judger", "ProgramOutputPath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::ProgramOutputPath failed!"<<endl;
            return false;
        }
        programOutputPath = buf;

        if(!ini.GetStringValue("Judger", "ProgramInputPath", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::ProgramInputPath failed!"<<endl;
            return false;
        }
        programInputPath = buf;


        if(!ini.GetStringValue("Judger", "ProgramWorkDir", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::ProgramWorkDir failed!"<<endl;
            return false;
        }
        programWorkDir = buf;

        int val;
        if(!ini.GetIntValue("Judger", "SandboxEnabled", val))
        {
            cerr<<"Read Judger::SandboxEnabled failed!"<<endl;
            return false;
        }
        sandboxEnabled = (val != 0);

        if(!ini.GetIntValue("Judger", "FSizeLimit", val))
        {
            cerr<<"Read Judger::FSizeLimit failed!"<<endl;
            return false;
        }
        fsizeLimit = (long)val;

        if(!ini.GetIntValue("Judger", "StackLimit", val))
        {
            cerr<<"Read Judger::StackLimit failed!"<<endl;
            return false;
        }
        stackLimit = (long)val;
        
        if(!ini.GetIntValue("Judger", "NProcLimit", val))
        {
            cerr<<"Read Judger::NProcLimit failed!"<<endl;
            return false;
        }
        nprocLimit  = (long)val;  

        if(!ini.GetIntValue("Judger", "NoFileLimit", val))
        {
            cerr<<"Read Judger::NoFileLimit failed!"<<endl;
            return false;
        }
        nofileLimit  = (long)val;

        if(!ini.GetIntValue("Judger", "JavaTimeFactor", val))
        {
            cerr<<"Read Judger::JavaTimeFactor failed!"<<endl;
            return false;
        }
        javaTimeFactor = (long)val;

        if(!ini.GetIntValue("Judger", "JavaMemoryFactor", val))
        {
            cerr<<"Read Judger::javaMemoryFactor failed!"<<endl;
            return false;
        }
        javaMemoryFactor = (long)val;

        if(!ini.GetStringValue("Judger", "ServerIP", buf, sizeof(buf)))
        {
            cerr<<"Read Judger::ServerIP failed!"<<endl;
            return false;
        }
        serverIp = buf;

        if(!ini.GetIntValue("Judger", "ServerPort", serverPort))
        {
            cerr<<"Read Judger::ServerPort failed!"<<endl;
            return false;
        }
        return true;
    }
    else
    {
        cerr<<"Open configuation file "<<configPath<<" failed!"<<endl;
        return false;
    }
}
