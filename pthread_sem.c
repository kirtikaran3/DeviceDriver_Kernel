#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
sem_t lock;
int arr[50];

void* writeit(void *wmsg)
{
	char *buf=(char *)wmsg;
	sem_wait(&lock);
	for(int i=0;i<50;i++)
	{
		arr[i]=i+1;
		printf("%s thread is writing\n",buf);
		
	}
	sem_post(&lock);
}
	
void* readit(void *rmsg)
{
	char *buf=(char *)rmsg;
	sem_wait(&lock);
	for(int i=0;i<50;i++)
	{
		printf("%s thread is reading and the value is %d\n",buf,arr[i]);
	}
	sem_post(&lock);
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	memset(arr,0,sizeof(arr));//memset intilizes the array with zero
	char *msg1="Thread1";
	char *msg2="Thread2";
	int sem_ret=sem_init(&lock,0,1);
	if(sem_ret<0)
	{
		printf("Falied to init sem.\n");
		exit(0);
	}
	int ret1=pthread_create(&thread1,NULL,writeit,(void *)msg1);
	int ret2=pthread_create(&thread2,NULL,readit,(void *)msg2);
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
	return 0;
}
