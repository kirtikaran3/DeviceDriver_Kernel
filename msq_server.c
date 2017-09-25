#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<pthread.h>

#define MSGSZ 128

typedef struct msgbuf
{
	long mtype;
	char mtext[MSGSZ];
} MSGBUF;

int main(int argc, char *argv[])
{
	while(1)
	{
		MSGBUF buf;
		key_t k=1234;
		int msqid=msgget(k, IPC_CREAT | 0666);
		if(msqid<0)
		{
			printf("Failed to create message queue.\n");
			exit(0);
		}
		buf.mtype=1;
		printf("Enter data to be sent to client.\n");
		fgets(buf.mtext, MSGSZ, stdin);
		strcat(buf.mtext,"*");
		int sret=msgsnd(msqid, &buf, MSGSZ, IPC_NOWAIT);
		if(sret<0)
		{
			printf("Failed to send message.\n");
			exit(0);
		}
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
	}
	return 0;
}
