#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main (void)
{
	int fd = open ("MyFile.txt", O_CREAT | O_WRONLY, 0600) ;
	if (fd < 0)
	{
		printf ("File could not be opened.\n") ;
		exit (0) ;
	}
	else
		printf ("MyFile.txt opened for writing.\n") ;
	ssize_t wr = write (fd, "Hello World!\n\0", 13) ;
	if (wr < 0)
	{
		printf ("Write Operation could not be performed.\n") ;
		exit (0) ;
	}
	else
		printf ("File Written in Successfuly.\n") ;
	close (fd);
	fd = open ("MyFile.txt", O_RDONLY, 0600) ;
	if (fd < 0)
	{
		printf ("File could not be opened.\n") ;
		exit (0);
	}
	else
		printf ("MyFile.txt opened for reading.\n") ;
	char buf[13];
	ssize_t rd = read (fd, buf, 13) ;
	if (rd < 0)
	{
		printf ("Read Operation could not be performed.\n") ;
		exit (0);
	}
	else
		printf ("The File MyFile.txt contains:\n%s",buf) ;
	close (fd) ;
	return 0 ;
}
