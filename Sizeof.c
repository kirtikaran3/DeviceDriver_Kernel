#include<stdio.h>
#include<malloc.h>
int main()
{
	int a[5]={1,2,3,4,5};
	int *p;//=(int *)malloc(sizeof(int)*5);
	//int i;
	//for(i=0;i<5;i++)
	//{
	//	p[i]=i+1;
	//}
	printf("Size of Each Member of a Static Array is %lu bytes.\n",(sizeof(a)/5));
	printf("Size of Each Member of a Dynamic Array is %lu bytes.\n",(sizeof(p)/1));
	return 0;
}
