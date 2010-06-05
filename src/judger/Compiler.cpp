#include "Compiler.h"
#include "Log.h"
#include "Configuration.h"

#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

bool GCCCompiler::Compile(int id)const
{
	char cmd[512] = {0};
	sprintf(cmd, "%s %s/%d.c -o %s/%d %s >/dev/null 2>&1", 
			cc.c_str(), srcPath.c_str(), id, destPath.c_str(), id, options.c_str());

	//log(Log::INFO)<<"The system command:"<<cmd<<endlog;
	return system(cmd) == 0;
}

bool GPPCompiler::Compile(int id)const
{
	char cmd[512] = {0};
	sprintf(cmd, "%s %s/%d.cpp -o %s/%d %s >/dev/null 2>&1", 
			cc.c_str(), srcPath.c_str(), id, destPath.c_str(), id, options.c_str());

	//log(Log::INFO)<<"The system command:"<<cmd<<endlog;
	return system(cmd) == 0;
}
bool PascalCompiler::Compile(int id)const{
	char cmd[512]={0};
	sprintf(cmd,"%s %s/%d.pas -o%s/%d >/dev/null 2>&1",
		cc.c_str(),srcPath.c_str(),id,destPath.c_str(),id);
	return system(cmd)==0;
}
bool JavaCompiler::Compile(int id)const{
	char cmd[512]={0};
	sprintf(cmd,"mkdir -p %s/%d >/dev/null 2>&1",destPath.c_str(),id);
		//Generate the destination folder java program needs.
	if(system(cmd)!=0){
		log(Log::ERROR)<<"Make destination folder failed."<<endlog;
		return false;
	}
	sprintf(cmd,"%s %s -d %s/%d %s/%d/Main.java >/dev/null 2>&1",cc.c_str(),options.c_str(),destPath.c_str(),id,srcPath.c_str(),id);
	if(system(cmd)!=0){
		log(Log::ERROR)<<"Compiler Main.java failed."<<endlog;
		return false;
	}
	sprintf(cmd,"%s %s -d %s/%d Loader.java >/dev/null 2>&1",cc.c_str(),options.c_str(),destPath.c_str(),id);
	if(system(cmd)!=0){
		log(Log::ERROR)<<"Compiler Loader.java failed."<<endlog;
		return false;
	}
	return true;
}

CompilerFactory::CompilerFactory()
    :compilers(3, (Compiler *)NULL)
{
}

int CompilerFactory::Initialize()
{
    char cmd[512];
    Configuration &conf = Configuration::GetInstance();
    bool flag = false;//indicates whether there's at least a compiler loading successfully
    sprintf(cmd, "which %s >/dev/null 2>&1", conf.GetCCompiler().c_str());
    if( system(cmd) == 0)
    {
        compilers[Compiler::COMPILER_GCC] = new GCCCompiler;
        compilers[Compiler::COMPILER_GCC]->SetCC(conf.GetCCompiler());
        compilers[Compiler::COMPILER_GCC]->SetOptions(conf.GetCCompilerOpt());

        flag = true;
        log(Log::INFO)<<"C compiler "<<conf.GetCCompiler()<<" loaded successfully."<<endlog;
    }
    else
    {
        log(Log::INFO)<<"C compiler "<<conf.GetCCompiler()<<" failed to load."<<endlog;
    }
    sprintf(cmd, "which %s >/dev/null 2>&1", conf.GetCppCompiler().c_str());
    if( system(cmd) == 0)
    {
        compilers[Compiler::COMPILER_GPP] = new GPPCompiler;
        compilers[Compiler::COMPILER_GPP]->SetCC(conf.GetCppCompiler());
        compilers[Compiler::COMPILER_GPP]->SetOptions(conf.GetCppCompilerOpt());

        flag = true;
        log(Log::INFO)<<"C++ compiler "<<conf.GetCppCompiler()<<" loaded successfully."<<endlog;
    }
    else
    {
        log(Log::INFO)<<"C++ compiler "<<conf.GetCppCompiler()<<" failed to load."<<endlog;
    }
    sprintf(cmd, "which %s >/dev/null 2>&1", conf.GetJavaCompiler().c_str());
    if( system(cmd) == 0 )
    {
        sprintf(cmd, "which %s >/dev/null 2>&1", conf.GetJavaRunner().c_str());
        if( system(cmd) == 0)
        {
            compilers[Compiler::COMPILER_JAVA] = new JavaCompiler;
            compilers[Compiler::COMPILER_JAVA]->SetCC(conf.GetJavaCompiler());
            compilers[Compiler::COMPILER_JAVA]->SetOptions(conf.GetJavaCompilerOpt());

            flag = true;
            log(Log::INFO)<<"Java compiler "<<conf.GetCppCompiler()<<" loaded successfully."<<endlog;
        }
        else
        {
            log(Log::INFO)<<"Java compiler "<<conf.GetCppCompiler()<<" failed to load."<<endlog;
        }
    }
    else
    {
        log(Log::INFO)<<"Java compiler "<<conf.GetCppCompiler()<<" failed to load."<<endlog;
    }

    sprintf(cmd, "which %s >/dev/null 2>&1", conf.GetPascalCompiler().c_str());
    if( system(cmd) == 0)
    {
        compilers[Compiler::COMPILER_PASCAL] = new PascalCompiler;
        compilers[Compiler::COMPILER_PASCAL]->SetCC(conf.GetPascalCompiler());
        //compilers[Compiler::COMPILER_PASCAL]->SetOptions(conf.GetCppCompilerOpt());

        flag = true;
        log(Log::INFO)<<"Pascal compiler "<<conf.GetPascalCompiler()<<" loaded successfully."<<endlog;
    }
    else
    {
        log(Log::INFO)<<"C++ compiler "<<conf.GetPascalCompiler()<<" failed to load."<<endlog;
    }

    if(!flag)
        return -1;//no compiler exists. so continueing running is meaningless

	for(vector<Compiler *>::iterator it = compilers.begin(); it != compilers.end(); ++it)
	{
        if(*it == NULL)
            continue;
		SetupCompiler(**it, Configuration::GetInstance().GetSrcFilePath(),
				Configuration::GetInstance().GetDestFilePath());
	}
	return 0;
}

CompilerFactory::~CompilerFactory()
{
	for(vector<Compiler *>::iterator it = compilers.begin(); it != compilers.end(); ++it)
    {
		if(*it)
            delete *it;
        *it = NULL;
    }
	compilers.clear();
}

Compiler *CompilerFactory::GetCompiler(const string &lan)
{
	if(lan == "c")
		return compilers[Compiler::COMPILER_GCC];
	else if(lan == "c++")
		return compilers[Compiler::COMPILER_GPP];
	else if(lan == "java")
		return compilers[Compiler::COMPILER_JAVA];
	else if(lan == "pascal")
		return compilers[Compiler::COMPILER_PASCAL];
	else
		return NULL;
}

Compiler *CompilerFactory::GetCompiler(Compiler::CompilerType type)
{
    return compilers[type];
}

void CompilerFactory::SetupCompiler(Compiler &compiler, const std::string &srcPath, const std::string &destPath)
{
	compiler.SetSrcPath(srcPath);
	compiler.SetDestPath(destPath);
}
