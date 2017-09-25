#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<pthread.h>
#include<semaphore.h>

#define MSGSZ 128

typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
} MSGBUF;

sem_t lock;
int msqid;
MSGBUF buf;

void* writeit()
{
	sem_wait(&lock);
	printf("Enter data to be sent to client.\n");
	fgets(buf.mtext, MSGSZ, stdin);
	strcat(buf.mtext,"*");
	int sret=msgsnd(msqid, &buf, MSGSZ, IPC_NOWAIT);
	if(sret<0)
	{
		printf("Failed to send message.\n");
		exit(0);
	}
	sem_post(&lock);
}
void* readit()
{
	sem_wait(&lock);
	ssize_t rret=msgrcv(msqid, &buf, MSGSZ, 1, 0);
	while(rret >= 0)
	{
		if(buf.mtext[strlen(buf.mtext)-1]!='*')
		{
			printf("Client says:\n");
			puts(buf.mtext);
			break;
		}
		ssize_t rret=msgrcv(msqid, &buf, MSGSZ, 1, 0);
	}
	if(rret<0)
	{
		printf("Failed to recieve message.\n");
		exit(0);
	}
	sem_post(&lock);	
}

int main(int argc, char *argv[])
{
	while(1)
	{
		key_t k=1234;
		pthread_t thread1, thread2;
		msqid=msgget(k, IPC_CREAT | 0666);
		if(msqid<0)
		{
			printf("Failed to create message queue.\n");
			exit(0);
		}
		buf.mtype=1;
		int sem_ret=sem_init(&lock,0,1);
		if(sem_ret<0)
		{
			printf("Falied to init sem.\n");
			exit(0);
		}
		int ret1=pthread_create(&thread1, NULL, writeit, NULL);
		int ret2=pthread_create(&thread2, NULL, readit, NULL);
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
		
	}
	return 0;
}
