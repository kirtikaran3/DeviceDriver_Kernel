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

void RDWR(int fd, struct sockaddr_in serv)
{
	char buf[SCKSZ];
	while(1)
	{
		socklen_t len=sizeof(serv);
		ssize_t rv=recvfrom(fd, &buf, SCKSZ, 0, (SA*) &serv, &len);
		if(rv<0)
		{
			printf("Failed to receive over Socket.\n");
			exit(0);
		}
		printf("Client says:\n%s",buf);
		printf("Enter data to be sent to client.\n");
		fgets(buf, SCKSZ, stdin);
		ssize_t sd=sendto(fd, &buf, SCKSZ, 0, (SA*) &serv, len);
		if(sd<0)
		{
			printf("Failed to send over Socket.\n");
			exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in serv, cli;
	socklen_t len;
	int serverfd;
	unlink("serverfd");
	serverfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(serverfd<0)
	{
		printf("Failed to create socket.\n");
		exit(0);
	}
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=htonl(INADDR_ANY);	
	serv.sin_port=htons(PORT);
	len=sizeof(serv);
	int bi=bind(serverfd, (SA*) &serv, len);
	if(bi<0)
	{
		printf("Failed to bind socket.\n");
		exit(0);
	}
	RDWR(serverfd, serv);
	close(serverfd);
	return 0;
}
