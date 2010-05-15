#include <stdio.h>

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	int a, b;
	while(n--)
	{
		scanf("%d%d", &a, &b);
		printf("%d-%d\n", a, b);
	}
	return 0;
}
