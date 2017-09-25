#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char *argv[])
{
	pid_t ret=fork();
	if(ret<0)
	{
		printf("Failed to fork.\n");
		exit(0);
	}
	else
	{
		if(ret==0)
		{
			//sleep(5);
			printf("Child Process.\n");
		}
		else
		{
			sleep(5);
			printf("Parent process.\n");
		}
	}
	return 0;
}
