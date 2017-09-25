#include<stdio.h>
#define MAXSIZE 50
void Print(int a[])
{
	printf("\n");
	for(int i=0;i<8;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void Swap(int *x, int *y)
{
	int t;
	t=*x;
	*x=*y;
	*y=t;
	return;
}
int Partition(int a[],int l,int h)
{
	int pivot=a[h];
	int i=l-1;//wall
	printf("\n--Wall is at %d.\n",i);
	for(int j=l;j<h;j++)
	{
		if(a[j]<=pivot)
		{
			i++;
			printf("\n--Wall is at %d after increment\n",i);
			Swap(&a[i], &a[j]);
			printf("\n--Swapped values are a[%d] %d and a[%d] %d\n",i,a[i],j,a[j]);
			Print(a);
		}
	}
	Swap(&a[i+1],&a[h]);
	printf("\n--Final Swapped values are a[%d] %d and a[%d] %d\n",i+1,a[i+1],h,a[h]);
	Print(a);
	return (i+1);
}
void QuickSort(int a[], int l,int h)
{
	printf("\n--0 l is %d and h is %d\n",l,h);
	if(h>l)
	{
		int pi=Partition(a,l,h);
		printf("\n--1 l is %d, h is %d and pi is %d\n",l,h,pi);
		QuickSort(a,l,pi-1);
		printf("\n--2 l is %d, h is %d and pi is %d\n",l,h,pi);
		QuickSort(a,pi+1,h);
	}
}
int main(void)
{
	int a[MAXSIZE]={56,23,1,4,12,16,32,8},n=8;
	/*printf("Enter the number of elements.\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter element number %d\n",i+1);
		scanf("%d",&a[i]);
	}*/
	QuickSort(a,0,n-1);
	printf("Sorted Array is \n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
