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

void writeit(int fd, int pm)
{
		char buf[SCKSZ];;
		pinMode(pm, OUTPUT);
		while(1)
		{
			printf("Enter 1 for high and 0 for low.\n");
			scanf("%s", buf);
			ssize_t sd=write(fd, &buf,SCKSZ);
			if(sd<0)
			{
				perror("Failed to send\n");
				exit (errno);
			}
		}
}						 

int main(int argc, char *argv[])
{
	wiringPiSetup();
	struct sockaddr_in serv, cli;
	socklen_t len;
	int servfd;
	int pm=7;
	unlink("servfd");
	servfd=socket(AF_INET, SOCK_STREAM, 0);
	if(servfd<0)
	{
		perror("Failed to create socket.\n");
		return errno;
	}
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=htonl(INADDR_ANY);
	serv.sin_port=htons(PORT);
	len=sizeof(serv);
	int bi=bind(servfd, (SA *) &serv, len);
	if(bi<0)
	{
		perror("Failed to bind socket.\n");
		return errno;
	}	
	int li=listen(servfd, 1);
	if(li<0)
	{
		perror("Failed to listen socket.\n");
		return errno;
	}
	printf("Server is listening...\n");
	int clifd=accept(servfd, (SA *) &cli, &len);
	if(clifd<0)
	{
		perror("Failed to accept socket.\n");
		return errno;
	}
	writeit(clifd, pm);
	close(clifd);
	close(servfd);
	return 0;
}