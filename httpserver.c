#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080

typedef struct sockaddr SA;

char webpage[]=
"HTTP/1.1 200 Ok\r\n"
"Content-type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>Test webpage for clients</title></head>\r\n"
"<body>Hello Client trying out a http file transfer.</body></html>\r\n";

int main(int argc, char *argv[])
{
	struct sockaddr_in serv, cli;
	int on=1;
	char buf[2048];
	socklen_t len;
	int serverfd;
	unlink("serverfd");
	serverfd=socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd<0)
	{
		printf("Failed to create socket.\n");
		exit(0);
	}
	setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
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
	pid_t pid=fork();
	if(pid==0)
	{
		close(serverfd);
		memset(buf, 0, 2048);
		read(clientfd, buf, 2047);
		printf("%s\n",buf);
		write(clientfd, webpage, sizeof(webpage)-1);
		close(clientfd);
	}
	close(clientfd);
	close(serverfd);
	return 0;
}
