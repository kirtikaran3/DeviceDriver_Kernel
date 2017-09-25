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

void RDWR(int fd, struct sockaddr_in cli)
{
	char buf[SCKSZ];
	while(1)
	{
		socklen_t len=sizeof(cli);
		printf("Enter data to be sent to server.\n");
		fgets(buf, SCKSZ, stdin);
		ssize_t sd=sendto(fd, &buf, SCKSZ, 0, (SA*) &cli, len);
		if(sd<0)
		{
			printf("Failed to send over Socket.\n");
			exit(0);
		}
		ssize_t rv=recvfrom(fd, &buf, SCKSZ, 0, (SA*) &cli, &len);
		if(rv<0)
		{
			printf("Failed to receive over Socket.\n");
			exit(0);
		}
		printf("Server says:\n%s",buf);
		
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in cli;
	int clientfd;
	unlink("clientfd");
	clientfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(clientfd<0)
	{
		printf("Failed to create socket.\n");
		exit(0);
	}
	cli.sin_family=AF_INET;
	cli.sin_addr.s_addr=htonl(INADDR_ANY);
	cli.sin_port=htons(PORT);
	RDWR(clientfd, cli);
	close(clientfd);
	return 0;
}
