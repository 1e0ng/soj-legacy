#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[], char* envp[])
{
	int *p1, *p2;
	p1 = new int;
	p2 = new int[5];
	*p1 = 2;
	p2[0] = p2[1] = p2[2] = p2[3] = p2[4] = *p1;
	vector<int> vi(100);
	for(size_t i = 0; i < vi.size(); i++)
		vi[i] = rand();
	for(vector<int>::iterator it = vi.begin(); it != vi.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	delete p1;
	delete []p2;
	
	int fd = open("a.out", O_WRONLY);
	write(fd, "fd\n", 3);
}
