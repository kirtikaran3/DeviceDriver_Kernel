#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define buflen 256
static char recv[buflen];

int main(int argc, char *argv[])
{
	int ret, fd;
	char string[buflen];
	printf("Starting device test..\n");
	fd=open("/dev/devchar", O_RDWR);
	if(fd<0)
	{
		perror("Failed to open the device..\n");
		return errno;
	}
	printf("Type in a short stirng to send to the kernel module\n");
	scanf("%[^\n]%*c",string);
	printf("Writing message to the device[%s].\n",string);
	ret=write(fd, string, strlen(string));
	if(ret<0)
	{
		perror("Failed to write the message to the deice...\n");
		return errno;
	}
	printf("Reading from the device...\n");
	ret=read(fd, recv, buflen);
	if(ret<0)
	{
		perror("Failed to read the message from the device.");
		return errno;
	}
	printf("The received message is [%s]\n",recv);
	return 0;
}
