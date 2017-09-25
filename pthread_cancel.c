#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>

void *msg(void *);

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	
	char *msg1="Thread1";
	char *msg2="Thread2";
	void *rett1, *rett2;
	printf("Creating a thread...\n");
	int ret1=pthread_create(&thread1,NULL,msg,(void *)msg1);
	int ret2=pthread_create(&thread2,NULL,msg,(void *)msg2);
	if(ret1<0 || ret2<0)
	{
		printf("Failed to create thread.\n");
		exit(0);
	}
	sleep(5);
	printf("Canceling Thread.\n");
	int retc1=pthread_cancel(thread1);
	int retc2=pthread_cancel(thread2);
	if(retc1<0 || retc2<0)
	{
		printf("Failed to join thread.\n");
		exit(0);
	}
	int retj1=pthread_join(thread1,&rett1);
	int retj2=pthread_join(thread2,&rett2);
	if(retj1<0 || retj2<0)
	{
		printf("Failed to join thread.\n");
		exit(0);
	}
	/*else
	{
		printf("%s returns %s.\n",msg1,(char *)rett1);
		printf("%s returns %s.\n",msg2,(char *)rett2);
	}*/
	return 0;
}

void *msg(void *myarg)
{
	char *msg=(char *)myarg;
	int sret=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	int tret=pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	if(sret<0 || tret<0)
	{
		printf("Failed to set thread.\n");
		exit(0);
	}
	for(int i=0;i<20;i++)
	{
		printf("Calling Thread is %s and called time is %d\n",msg,i+1);
		sleep(1);
	}
	pthread_exit("Returning back to main thread");
}
