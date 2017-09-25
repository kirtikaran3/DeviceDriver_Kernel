#include<stdio.h>
void Even(int *x, int *y)
{
	int i;
	printf("Even nmbers between %d and %d are:\n",*x,*y);
	for(i=*x;i<=*y;i++)
	{
		if(i%2==0)
			printf("%d ",i);
	}
	printf("\n");
}
int main(void)
{
	int x,y;
	printf("Enter two numbers beteen which even numbers are to found.\n");
	scanf("%d %d",&x,&y);
	Even(&x,&y);
	return 0;
}
