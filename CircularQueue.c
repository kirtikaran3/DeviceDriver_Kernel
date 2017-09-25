#include<stdio.h>
#define MAXSIZE 5
struct CircularQueue
{
	int cque[MAXSIZE];
	int front,rear;
};
typedef struct CircularQueue CQUEUE;
CQUEUE q;
void push(void)
{
	int num;
	if(q.front+q.rear==MAXSIZE-1||q.front==q.rear+1)
	{
		printf("Queue is Full.\n");
		return;
	}
	else if(q.rear==-1)
		q.front = q.rear = 0;
	else if(q.rear==MAXSIZE-1)
		q.rear=0;
	else
		q.rear++;
	printf("Enter a number.\n");
	scanf("%d",&num);
	q.cque[q.rear]=num;
	return;
}
int pop(void)
{
	int num;
	if(q.front==-1)
	{
		printf("Queue is Empty.\n");
		return -1;
	}
	else
	{
		num=q.cque[q.front];
		if(q.front==q.rear)
			q.front = q.rear = -1;
		else if(q.front==MAXSIZE-1)
			q.front = 0;
		else
			q.front++;
	}
	printf("The popped number is %d.\n",num);
	return num;	
}
void display(void)
{
	int i;
	if(q.front==-1)
	{
		printf("Queue is Empty.\n");
		return;
	}
	else if(q.rear>=q.front)
	{
		for(i=q.front;i<=q.rear;i++)
			printf("%d ",q.cque[i]);
		printf("\n");
	}
	else
	{
		for(i=0;i<=q.rear;i++)
			printf("%d ",q.cque[i]);
		for(i=q.front;i<MAXSIZE;i++)
			printf("%d ",q.cque[i]);
		printf("\n");
	}
	return;
}
int main(void)
{
	int option=1;
	int choice;
	q.front=-1;
	q.rear=-1;
	while(option)
	{
		printf("1. Push.\n");
		printf("2. Pop.\n");
		printf("3. Display.\n");
		printf("Enter a choice.\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				push();
				break;
			case 2:
				pop();
				break;
			case 3:
				display();
				break;
			default:
				return 0;
		}
		printf("Do you want to continue (Enter 0 or 1)?\n");
		scanf("%d",&option);
	}
	return 0;
}
		
