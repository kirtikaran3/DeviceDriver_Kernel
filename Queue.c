#include<stdio.h>
#define MAXSIZE 5
struct queue
{
	int que[MAXSIZE];
	int rear;
	int front;
};
typedef struct queue QUEUE;
QUEUE q;
void push(void)
{
	int num;
	if(q.rear==MAXSIZE-1)
	{
		printf("Queue is full.\n");
		return;
	}
	else
	{
		if(q.front==-1)
		{
			q.front=0;
		}
		printf("Enter the element to be insereted.\n");
		scanf("%d",&num);
		q.rear=q.rear+1;
		q.que[q.rear]=num;
	}
	
	return;
}
int pop(void)
{
	int num;
	if(q.front==-1 || q.front>q.rear)
	{
		printf("Queue is empty.\n");
		q.front=-1;
		q.rear=-1;
		return q.front;
	}
	else
	{
		num=q.que[q.front];
		printf("The poped element is %d\n",num);
		q.front=q.front+1;
	}
	return num;
}
void display(void)
{
	int i;
	if(q.front==-1 || q.front>q.rear)
	{
		printf("Queue is empty.\n");
		return;
	}
	else
	{
		printf("Queue is :\n");
		for(i=q.front;i<=q.rear;i++)
		{
			printf("%d ",q.que[i]);
		}
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
	printf("Queue Operation.\n");
	while(option)
	{
		printf("1 --> Push.\n");
		printf("2 --> Pop.\n");
		printf("3 --> Display.\n");
		printf("4 --> Exit.\n");
		printf("Select an option.\n");
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
		fflush(stdin);
		printf("Do you want to continue (Enter 0 or 1).\n");
		scanf("%d",&option);
	}
	return 0;
}	
