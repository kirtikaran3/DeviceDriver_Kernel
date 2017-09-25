#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
	int i=1,s=0;
	while(i<argc)
	{
		printf("Argument %d is %s\n",i,argv[i]);
		i++;
	}
	i=1;
	while(i<argc)
	{
		s=s+atoi(argv[i]);
		i++;
	}
	if(argc>1)
		printf("Sum of the arguments is %d\n", s);
	return 0;
}
