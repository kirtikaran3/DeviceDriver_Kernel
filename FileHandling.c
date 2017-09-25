#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	FILE *f ;
	f = fopen ("File.txt", "w") ;
	if (f==NULL)
	{
		printf ("File could not be opened.\n") ;
		exit (0) ;
	}
	else
		printf ("File opened for writing.\n") ;
	const char *write = "Hello World!\n" ;
	fwrite (write, 13, 1, f) ;
	if (ferror (f) != 0)
	{
		printf ("Write operation could not be performed.\n") ;
		exit (0) ;
	}
	else
		printf ("File written in successfully.\n") ;
	fclose (f) ;
	f = fopen ("File.txt", "r") ;
	if (f==NULL)
	{
		printf("File could not be opened for reading.\n") ;
		exit (0) ;
	}
	else
		printf ("File opened for reading.\n") ;
	clearerr (f) ;
	char read[13] ;
	fread (&read, 13, 1, f) ;
	if (ferror (f) != 0)
	{
		printf ("Read operation could not be performed.\n") ;
		exit (0) ;
	}
	else
		printf ("The File File.txt contains:\n%s",read) ;
	fclose (f) ;
	return 0 ;
}
