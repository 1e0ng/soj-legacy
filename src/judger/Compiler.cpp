#include "Compiler.h"
//#include "Log.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

string Compiler::ComposePathname(const string &path, const string &filename)
{
	if(path.empty())
		return filename;
	else
	{
		if(path[path.length() - 1] != '/')//does the srcPath ends with a '/'?
			return path + "/" + filename;
		else
			return path + filename;
	}
}

bool Compiler::Compile()const
{
	char cmd[512] = {0};
	if(bLogOutput)
	{
		sprintf(cmd, "%s %s -o %s %s > %s", 
				GetCC().c_str(), GetSrcPathname().c_str(), GetDestPathname().c_str(), GetOptions().c_str(), GetLogPathname().c_str());
	}
	else
	{
		sprintf(cmd, "%s %s -o %s %s",
				GetCC().c_str(), GetSrcPathname().c_str(), GetDestPathname().c_str(), GetOptions().c_str());
	}
	return system(cmd) == 0;
}

CompilerFactory::CompilerFactory()
{
	compilers.push_back(new GCCCompiler());
	compilers.push_back(new GPPCompiler());
	compilers.push_back(new JavaCompiler());
}

CompilerFactory::~CompilerFactory()
{
	for(vector<Compiler *>::iterator it = compilers.begin(); it != compilers.end(); ++it)
		delete *it;
}

CompilerFactory *CompilerFactory::instance = NULL;

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
