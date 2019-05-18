#include <stdio.h>

int main(int argc, const char* argv[])
{
	int i =1;
	while(i-1>=0)
	{
		i = i*2;
		printf("%d\t", i-1);
	}
	printf("0X80000001 = %i\n", 0X80000001);
	return 0;
}
