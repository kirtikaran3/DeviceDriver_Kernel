#include<stdio.h>
#include<malloc.h>
int main(void)
{	
	int i;
	int *p=(int *)malloc(sizeof(int)*5);
	int *q=(int *)calloc(5,sizeof(int));
	for(i=0;i<5;i++)
	{
		printf("Enter element %d.\n",i+1);
		scanf("%d",&p[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("%d ",p[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("Enter element %d.\n",i+1);
		scanf("%d",&q[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("%d ",q[i]);
	}
	p=(int *)realloc(p,sizeof(int)*10);
	for(i=0;i<5;i++)
	{
		p[i+5]=q[i];
	}
	printf("\n");
	for(i=0;i<10;i++)
	{
		printf("%d ",p[i]);
	}
	printf("\n");
	return 0;
}
