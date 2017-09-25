#include <stdio.h>
#include <stdlib.h>
int main (int argc, char * argv[])
{
	int max = atoi (argv[1]), pos = 1 ;
	if (argc == 1)
	{
		printf ("Rerun and enter integers.\n") ;
		return 0 ;
	}
	for (int i = 2; i < argc; i++)
	{
		if (max < atoi (argv[i]))
		{
			max = atoi (argv[i]) ;
			pos = i+1 ;
		}
	}
	printf ("Largest Value is %d at position %d.\n",max,pos) ;
	return 0 ;
}
