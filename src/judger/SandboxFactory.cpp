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
	sandboxes.clear();
}

int SandboxFactory::Initialize()
{
	return 0;
}

Sandbox *SandboxFactory::GetSandbox(const string &type)const
{
	if(type == "native")
		return sandboxes[0];
	else
		return NULL;
}
