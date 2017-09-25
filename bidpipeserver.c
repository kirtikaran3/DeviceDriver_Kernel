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
	char buf[100];
	while(1)
	{
		int fd=open("datafile",O_WRONLY);
		if(fd<0)
		{
			printf("Failed to open file.\n");
			close(fd);
			exit(0);
		}
		else
		{
			printf("Enter data to send to client.\n");
			fgets(buf,100,stdin);
			int wret=write(fd,buf,100);
			if(wret<0)
			{
				printf("Failed to Write.\n");
				close(fd);
				exit(0);
			}
			else
			{
				printf("Sent data to client: %s",buf);
				close(fd);
			}
		}
		int ret=mkfifo("datafile",0600);
		fd=open("datafile",O_RDONLY);
		if(fd<0)
		{
			printf("Failed to open file.\n");
			exit(0);
		}
		else
		{
			int rret=read(fd,buf,100);
			if(rret<0)
			{
				printf("Failed to Read.\n");
				close(fd);
				unlink("datafile");
				exit(0);
			}
			else
			{
				printf("Client says: %s",buf);
				close(fd);
				//unlink("datafile");
			}
		}
		
	}
	return 0;
}
