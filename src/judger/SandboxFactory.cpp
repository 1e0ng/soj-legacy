#include "Sandbox.h"
#include "NativeSandbox.h"

#include <assert.h>

using namespace std;

SandboxFactory::SandboxFactory()
{
	sandboxes.push_back(new NativeSandbox());
}

SandboxFactory::~SandboxFactory()
{
	for(vector<Sandbox *>::iterator it = sandboxes.begin(); it != sandboxes.end(); ++it)
		delete *it;
}

int SandboxFactory::Initialize()
{
	return 0;
}

Sandbox *SandboxFactory::GetSandbox(const string &lan)const
{
	if(lan == "c" || lan == "c++")
		return sandboxes[0];
	else
		return NULL;
}
