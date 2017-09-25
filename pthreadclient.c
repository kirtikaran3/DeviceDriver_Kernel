#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
char buf[100];
int fd;
pthread_mutex_t lock;
void* writeit()
{
	pthread_mutex_lock(&lock);
	printf("Enter data to send to server.\n");
	fgets(buf,100,stdin);
	int wret=write(fd,buf,100);
	if(wret<0)
	{
		printf("Failed to Write.\n");
		close(fd);
		pthread_mutex_unlock(&lock);
		exit(0);
	}
	else
	{
		printf("Sent data to server: %s",buf);
		close(fd);
	}
	pthread_mutex_unlock(&lock);
}
void* readit()
{
	pthread_mutex_lock(&lock);
	int rret=read(fd,buf,100);
	if(rret<0)
	{
		printf("Failed to Read.\n");
		close(fd);
		unlink("datafile");
		pthread_mutex_unlock(&lock);
		exit(0);
	}
	else
	{
		printf("Server says: %s",buf);
		close(fd);
		//unlink("datafile");
	}
	pthread_mutex_unlock(&lock);
}
int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	while(1)
	{
		int ret=mkfifo("datafile",0600);
		fd=open("datafile",O_RDONLY);
		if(fd<0)
		{
			printf("Failed to open file.\n");
			close(fd);
			exit(0);
		}
		else
		{
			int ret1=pthread_create(&thread1,NULL,readit,NULL);
			if(ret1<0)
			{
				printf("Failed to create threads.\n");
				exit(0);
			}
			int retj1=pthread_join(thread1,NULL);
			if(retj1<0)
			{
				printf("Failed to join threads.\n");
				exit(0);
			}
		}
		fd=open("datafile",O_WRONLY);
		if(fd<0)
		{
			printf("Failed to open file.\n");
			exit(0);
		}
		else
		{
			int ret2=pthread_create(&thread2,NULL,writeit,NULL);
			if(ret2<0)
			{
				printf("Failed to create threads.\n");
				exit(0);
			}
			int retj2=pthread_join(thread2,NULL);
			if(retj2<0)
			{
				printf("Failed to join threads.\n");
				exit(0);
			}
		}
	}
	return 0;
}
