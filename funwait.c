#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void msg(const char *, int);

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
			msg("child",10);
		}
		else
		{
			//wait(NULL);
			msg("parent",20);
		}
	}
	return 0;
}
void msg(const char *m, int n)
{
	int i=0;
	while(i<n)
	{
		printf("Function called by %s.\n",m);
		i++;
		sleep(1);
	}
	return;
}
