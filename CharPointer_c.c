#include<stdio.h>

int main(void)
{
	char *p[]={
			"Linux",
			"macOS",
			"Windows"
		  };
	int i,j;
	for(j=0;j<3;j++)
	{
	
		for(i=0;*(*(p+j)+i)!='\0';i++)
		{
			printf("%c ",*(*(p+j)+i));
		}
	}
	return 0;
}
