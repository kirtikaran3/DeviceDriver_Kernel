#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	int fd[2],ret;
	pid_t pid;
	char buf[15];
	ret=pipe(fd);
	if(ret<0)
	{
		printf("Failed to create a pipe.\n");
		exit(0);
	}
	else
	{
		pid=fork();
		if(pid<0)
		{
			printf("Failed to fork.\n");
			exit(0);
		}
		else
		{
			if(pid==0)
			{
				printf("Child Process...\n");
				read(fd[0],buf,12);
				printf("Child reads %s",buf);
				write(fd[1],"Hello Parent\n",13);
				printf("Child writes Hello Parent\n");
			}
			else
			{
				printf("Parent Process...\n");
				write(fd[1],"Hello Child\n",12);
				printf("Parent write Hello Child\n");
				wait(NULL);
				printf("Parent Process...\n");
				read(fd[0],buf,13);
				printf("Parent Reads %s\n",buf);
			}
		}
	}
	return 0;
}
