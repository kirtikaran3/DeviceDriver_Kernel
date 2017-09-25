#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	int fd=open("datafile",O_CREAT | O_WRONLY);
	if(fd<0)
	{
		printf("Failed to open file.\n");
		exit(0);
	}
	else
	{
		int wret=write(fd,"Hello Client\n",13);
		if(wret<0)
		{
			printf("Failed to Write.\n");
			exit(0);
		}
		else
		{
			printf("Sent data to client.\n");
			close(fd);
		}
	}
	return 0;
}
