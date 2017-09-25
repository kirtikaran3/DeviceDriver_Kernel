#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<wiringPi.h>

#define PORT 9734
#define SCKSZ 4

typedef struct sockaddr SA;

void readit(int fd, int pm)
{
		char buf[SCKSZ];
		int s;
		pinMode(pm, OUTPUT);
		while(1)
		{
			ssize_t rv=read(fd,&buf,SCKSZ);
			if(rv<0)
			{
				perror("Failed to receive\n");
				exit (errno);
			}
			s=atoi(buf);
			digitalWrite(pm, s);
		}
}						 

int main(int argc, char *argv[])
{
	wiringPiSetup();
	struct sockaddr_in cli;
	socklen_t len;
	int clifd;
	int pm=7;
	unlink("clifd");
	clifd=socket(AF_INET, SOCK_STREAM, 0);
	if(clifd<0)
	{
		perror("Failed to create socket.\n");
		return errno;
	}
	cli.sin_family=AF_INET;
	cli.sin_addr.s_addr=inet_addr("127.0.0.1");
	cli.sin_port=htons(PORT);
	len=sizeof(cli);
	int ct=connect(clifd, (SA *) &cli, len);
	if(ct<0)
	{
		perror("Failed to connect socket.\n");
		return errno;
	}	
	readit(clifd, pm);
	close(clifd);
	return 0;
}