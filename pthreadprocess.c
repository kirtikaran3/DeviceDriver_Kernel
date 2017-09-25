#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>

void* EXEC()
{
	printf("Parent Process...\n");
	printf("EXEC()-- pid: %d and ppid: %d\n",getpid(),getppid());
	int ret=execl("./pthread.out","\0",NULL);
	printf("Should Not run.\n");
}
void* FORK()
{
	printf("Parent Process before fork()\n");
	printf("FORK-- pid: %d and ppid: %d\n",getpid(),getppid());
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
			printf("Child Process after fork()\n");
			printf("FORK-- pid: %d and ppid: %d\n",getpid(),getppid());
		}
		else
		{
			printf("Parent Process after fork().\n");
			printf("FORK-- pid: %d and ppid: %d\n",getpid(),getppid());
		}
	}
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	printf("Creating a thread...\n");
	int ret1=pthread_create(&thread1,NULL,EXEC,NULL);
	int ret2=pthread_create(&thread2,NULL,FORK,NULL);
	if(ret1<0 || ret2<0)
	{
		printf("Failed to create thread.\n");
		exit(0);
	}
	int rett1=pthread_join(thread1,NULL);
	int rett2=pthread_join(thread2,NULL);
	if(rett1<0 || rett2<0)
	{
		printf("Failed to join thread.\n");
		exit(0);
	}
	return 0;
}
