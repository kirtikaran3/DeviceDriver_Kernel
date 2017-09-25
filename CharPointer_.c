#include<stdio.h>

int main(void)
{
	char *p[]={
			"Linux",
			"macOS",
			"Windows"
		  };
	int i;
	for(i=0;i<4;i++) // Error: Segmentation Fault
	{
		printf("%s",*(p+i));
		printf("\n");
	}
	return 0;
}
