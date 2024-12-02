#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int i;
	int num;

	if(argc < 1)
	{
		printf("hello\n");
	}
	else
	{
		num = atoi(argv[1]);
		printf("hello");

		for(i=0; i<num; i++)
			fork();
		printf("\n");
	}
	return 0;
}
