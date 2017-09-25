#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int a[]={0};
int main(int argc, char *argv[])
{
	pid_t ret=fork();
	if(ret<0)
	{
		printf("Failed to fork.\n");
		exit(0);
	}
	else
	{
		int *p=a;
		if(ret==0)
		{
			printf("Child Process.\n");
			printf("The value is %d.\n",a[0]);
		}
		else
		{
			printf("Parent process.\n");
			printf("The value before increment: %d\n",a[0]);
			(*p)++;
			printf("The value after increment: %d\n",a[0]);
		}
	}
	return 0;
}
