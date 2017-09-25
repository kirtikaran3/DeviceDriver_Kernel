#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>

void *sum();

int main(int argc, char *argv[])
{
	pthread_t thread1;
	printf("Creating a thread...\n");
	int ret1=pthread_create(&thread1,NULL,sum,NULL);//no argument
	if(ret1<0)
	{
		printf("Failed to create thread.\n");
		exit(0);
	}
	int retj1=pthread_join(thread1,NULL);
	if(retj1<0)
	{
		printf("Failed to join thread.\n");
		exit(0);
	}
	return 0;
}

void *sum()//no argument
{
	long long int s=0;
	for(int i=0;i<10000000000;i++)//Use of Full Core
	{
		s+=(i+1);
	}
	printf("Sum is %lld\n",s);
	return 0;
}
