#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	int ret=mkfifo("datafile",0600);
	if(ret<0)
	{
		printf("Failed to connect pipe.\n");
		unlink("datafile");
		exit(0);
	}
	else
	{
		int fd=open("datafile", O_RDONLY);
		if(fd<0)
		{
			printf("Failed to open file.\n");
			close(fd);
			unlink("datafile");
			exit(0);
		}
		else
		{
			char buf[13];
			int rret=read(fd,buf,13);
			if(rret<0)
			{
				printf("Failed to Read.\n");
				close(fd);
				unlink("datafile");
				exit(0);
			}
			else
			{
				printf("Server says: %s",buf);
				close(fd);
				unlink("datafile");
			}
		}
	}
	return 0;
}
