#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[])
{
	struct stat buf;
	char bbuf[100];
	int fd=open("memmap.txt", O_RDWR);
	if(fd<0)
	{
		perror("Failed to open file.\n");
		exit(-1);
	}	
	int ret=fstat(fd, &buf);
	if(ret<0)
	{
		perror("Failed to get stats.\n");
		exit(-1);
	}
	void* map=mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	int red=read(fd, (void *) &bbuf, buf.st_size);
	for(int i=0;bbuf[i]!='\0';i++)
	{
		if(isupper(bbuf[i]))
		{
			bbuf[i]=tolower(bbuf[i]);
		}
		else if(islower(bbuf[i]))
		{
			bbuf[i]=toupper(bbuf[i]);
		}
	}
	off_t ls=lseek(fd, 0, SEEK_SET);
	int wrt=write(fd, (void *) &bbuf, 45);
	close(fd);	
	return 0;
}
