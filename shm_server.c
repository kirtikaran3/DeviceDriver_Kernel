#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define SHMSIZE 100

int main(int argc, char *argv[])
{
	char *status;
	char s[]="*";
	key_t key=9876;
	int shmid=shmget(key,SHMSIZE,IPC_CREAT | 0666);
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
	while(1)
	{
		printf("Enter data to send to client.\n");
		fgets(status,100,stdin);
		printf("Data sent is %s",status);
		strcat(status,s);
		while(status[strlen(status)-1]=='*')
		{
			sleep(1);	
		}
		int i=0;
		printf("Client Says:\n");
		do
		{
			printf("%c",status[i]);
			i++;
		}
		while(status[i]!='\n');
		printf("%c",status[i]);
	}
	shmdt(status);	
	return 0;
}
