#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 9734
#define SCKSZ 128

typedef struct sockaddr SA;

void RDWR(int fd)
{
	char buf[SCKSZ];
	while(1)
	{
		ssize_t rv=read(fd, &buf, SCKSZ);
		if(rv<0)
		{
			printf("Failed to receive over Socket.\n");
			exit(0);
		}
		printf("Server says:\n%s",buf);
		printf("Enter data to be sent to server.\n");
		fgets(buf, SCKSZ, stdin);
		ssize_t sd=write(fd, &buf, SCKSZ);
		if(sd<0)
		{
			printf("Failed to send over Socket.\n");
			exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in cli;
	socklen_t len;
	int clientfd;
	unlink("clientfd");
	clientfd=socket(AF_INET, SOCK_STREAM, 0);
	if(clientfd<0)
	{
		printf("Failed to create socket.\n");
		exit(0);
	}
	cli.sin_family=AF_INET;
	cli.sin_addr.s_addr=inet_addr("127.0.0.1");
	cli.sin_port=htons(PORT);
	len=sizeof(cli);
	int ct=connect(clientfd, (SA*) &cli, len);
	if(ct<0)
	{
		printf("Failed to connect to server.\n");
		exit(0);
	}
	RDWR(clientfd);
	close(clientfd);
	return 0;
}
