#include<stdio.h>

extern int sum(int *, int *);

int main(int argc, char *argv[])
{
	int a,b,c;
	printf("Enter two intergers.\n");
	scanf("%d %d",&a,&b);
	c=sum(&a,&b);
	printf("The sum of %d and %d is %d\n",a,b,c);
	return 0;
}
