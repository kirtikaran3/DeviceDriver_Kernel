#include<stdio.h>
#define MAXSIZE 50
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
	int i=l-1;
	for(int j=l;j<h;j++)
	{
		if(a[j]<=pivot)
		{
			i++;
			Swap(&a[i], &a[j]);
		}
	}
	Swap(&a[i+1],&a[h]);
	return (i+1);
}
void QuickSort(int a[], int l,int h)
{
	if(h>l)
	{
		int pi=Partition(a,l,h);
		QuickSort(a,l,pi-1);
		QuickSort(a,pi+1,h);
	}
}
int main(void)
{
	int a[MAXSIZE],n;
	printf("Enter the number of elements.\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter element number %d\n",i+1);
		scanf("%d",&a[i]);
	}
	QuickSort(a,0,n-1);
	printf("Sorted Array is \n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
