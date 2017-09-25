#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define QUERY_SET_VALUE _IOR('q', 1, int *)
#define QUERY_CLEAR_VALUE _IO('q', 2) 
#define QUERY_GET_VALUE _IOW('q', 3, int *)


int main(int argc, char *argv[])
{
	int ret, fd;
	int a;
	printf("Starting device test..\n");
	fd=open("/dev/devchar", O_RDWR);
	if(fd<0)
	{
		perror("Failed to open the device..\n");
		return errno;
	}
	printf("Enter an integer\n");
	scanf("%d",&a);
	printf("Writing message to the device[%d].\n",a);
	ret=ioctl(fd, QUERY_SET_VALUE, &a);
	if(ret<0)
	{
		perror("Failed to set value.\n");
		return errno;
	}
	/*ret=write(fd, string, strlen(string));
	if(ret<0)
	{
		perror("Failed to write the message to the deice...\n");
		return errno;
	}*/
	printf("Reading from the device...\n");
	ret=ioctl(fd, QUERY_GET_VALUE, &a);
	if(ret<0)
	{
		perror("Failed to set value.\n");
		return errno;
	}
	/*ret=write(fd, string, strlen(string));
	/*ret=read(fd, recv, buflen);
	if(ret<0)
	{
		perror("Failed to read the message from the device.");
		return errno;
	}*/
	printf("The received message is [%d]\n",a);
	return 0;
}
