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
	sprintf(cmd, "%s %s/%d.c -o %s/%d %s 2>/dev/null", 
			cc.c_str(), srcPath.c_str(), id, destPath.c_str(), id, options.c_str());

	log(Log::INFO)<<"The system command:"<<cmd<<endlog;
	return system(cmd) == 0;
}

bool GPPCompiler::Compile(int id)const
{
	char cmd[512] = {0};
	sprintf(cmd, "%s %s/%d.cpp -o %s/%d %s 2>/dev/null", 
			cc.c_str(), srcPath.c_str(), id, destPath.c_str(), id, options.c_str());

	log(Log::INFO)<<"The system command:"<<cmd<<endlog;
	return system(cmd) == 0;
}

CompilerFactory::CompilerFactory()
{
	compilers.push_back(new GCCCompiler());
	compilers.push_back(new GPPCompiler());
	compilers.push_back(new JavaCompiler());
}

int CompilerFactory::Initialize()
{
	for(vector<Compiler *>::iterator it = compilers.begin(); it != compilers.end(); ++it)
	{
		SetupCompiler(**it, Configuration::GetInstance().GetSrcFilePath(),
				Configuration::GetInstance().GetDestFilePath());
	}
	return 0;
}

CompilerFactory::~CompilerFactory()
{
	for(vector<Compiler *>::iterator it = compilers.begin(); it != compilers.end(); ++it)
		delete *it;
	compilers.clear();
}

Compiler *CompilerFactory::GetCompiler(const string &lan)
{
	if(lan == "c")
		return compilers[0];
	else if(lan == "c++")
		return compilers[1];
	else if(lan == "java")
		return compilers[2];
	else
		return NULL;
}

void CompilerFactory::SetupCompiler(Compiler &compiler, const std::string &srcPath, const std::string &destPath)
{
	compiler.SetSrcPath(srcPath);
	compiler.SetDestPath(destPath);
}
