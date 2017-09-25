#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define SHMSIZE 100
sem_t lock;
char *status;
char s[]="*";
void* writeit(void * s)
{
	sem_wait(&lock);
	printf("Enter data to send to client.\n");
	fgets(status,100,stdin);
	printf("Data sent is %s",status);
	sem_post(&lock);
	while(status[strlen(status)-1]!='*')
	{
		sleep(1);
	}
}
void* readit(void * s)
{
	sem_wait(&lock);
	int i=0;
	printf("Server Says:\n");
	do
	{
		printf("%c",status[i]);
		i++;
	}
	while(status[i]!='\n');
	printf("%c",status[i]);
	sem_post(&lock);
}
int main(int argc, char *argv[])
{
	while(1)
	{
		key_t key=9876;
		int shmid=shmget(key,SHMSIZE,0666);
		if(shmid<0)
		{
			printf("Failed to create shared memory.\n");
			exit(0);
		}
		status=shmat(shmid,NULL,0);
		if(status==(char *) -1)
		{
			printf("Failed to attach shared memory.\n");
			exit(0);
		}
		int sem_ret=sem_init(&lock,0,1);
		if(sem_ret<0)
		{
			printf("Falied to init sem.\n");
			exit(0);
		}
		pthread_t thread1,thread2;
		int ret1=pthread_create(&thread1,NULL,readit,(void *)status);
		int ret2=pthread_create(&thread2,NULL,writeit,(void *)status);
		if(ret1<0 || ret2<0)
		{
			printf("Failed to create threads.\n");
			exit(0);
		}
		int retj1=pthread_join(thread1,NULL);
		int retj2=pthread_join(thread2,NULL);
		if(retj1<0 || retj2<0)
		{
			printf("Failed to join threads.\n");
			exit(0);
		}
		sem_destroy(&lock);
		shmdt(status);
	}
	return 0;
}
