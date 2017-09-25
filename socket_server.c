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
		printf("Enter data to be sent to client.\n");
		fgets(buf, SCKSZ, stdin);
		ssize_t sd=write(fd, &buf, SCKSZ);
		if(sd<0)
		{
			printf("Failed to send over Socket.\n");
			exit(0);
		}
		ssize_t rv=read(fd, &buf, SCKSZ);
		if(rv<0)
		{
			printf("Failed to receive over Socket.\n");
			exit(0);
		}
		printf("Client says:\n%s",buf);
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_in serv, cli;
	socklen_t len;
	int serverfd;
	unlink("serverfd");
	serverfd=socket(AF_INET, SOCK_STREAM, 0);
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
	int li=listen(serverfd, 5);
	if(li<0)
	{
		printf("Failed to listen socket.\n");
		exit(0);
	}
	printf("Server is Listening...\n");
	len=sizeof(cli);
	int clientfd=accept(serverfd, (SA*) &cli, &len);
	if(clientfd<0)
	{
		printf("Failed to accept client.\n");
		exit(0);
	}
	RDWR(clientfd);
	close(clientfd);
	close(serverfd);
	return 0;
}
