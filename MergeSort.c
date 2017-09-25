#include<stdio.h>
#define MAXSIZE 50
void MergeSort(int a[],int b,int m,int e);
void Partition(int a[],int b, int e)
{
	int m;
	if(e>b)
	{
		m=(b+e)/2;
		Partition(a,b,m);
		Partition(a,m+1,e);
		MergeSort(a,b,m,e);
	}
	return;
}
void MergeSort(int a[], int b, int m, int e)
{
	int i,n,j,k,l,t[MAXSIZE];
	l=b;
	i=b;
	n=m+1;
	while(l<=m && n<=e)
	{
		if(a[l]<=a[n])
		{
			t[i]=a[l];
			l++;
		}
		else
		{
			t[i]=a[n];
			n++;
		}
		i++;
	}
	if(l>m)
	{
		for(k=n;k<=e;k++)
		{
			t[i]=a[k];
			i++;
		}
	}
	else
	{
		for(k=l;k<=m;k++)
		{
			t[i]=a[k];
			i++;
		}
	}
	for(k=b;k<=e;k++)
	{
		a[k]=t[k];
	}
	return;
}
int main(void)
{
	int a[MAXSIZE],n;
	printf("Enter the size of the Array.\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter the elemenet %d \n",i+1);
		scanf("%d",&a[i]);
	}
	Partition(a,0,n-1);
	printf("The Sorted Array is:\n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
