#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *const argv[])
{
	printf("Parent Process calling execv...\n");
	int ret = execv("./process.out", argv);
	printf("Failed execv...\n");
	return 0;
}
