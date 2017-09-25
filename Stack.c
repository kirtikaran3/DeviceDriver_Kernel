#include<stdio.h>
#define MAXSIZE 5
struct stack
{
	int stk[MAXSIZE];
	int top;
};
typedef struct stack STACK;
STACK s;
void push(void)
{
	int num;
	if(s.top==(MAXSIZE-1))
	{
		printf("Stack is full.\n");
		return;
	}
	else
	{
		printf("Enter the element to be pushed.\n");
		scanf("%d",&num);
		s.top=s.top+1;
		s.stk[s.top]=num;
	}
	return;
}
int pop(void)
{
	int num;
	if(s.top==-1)
	{
		printf("The stack is empty.\n");
		return (s.top);
	}
	else
	{
	 	num=s.stk[s.top];
		printf("The poped element is %d.\n",num);
		s.top=s.top-1;
	}
	return num;
}
void display(void)
{
	if(s.top==-1)
	{
		printf("The stack is empty.\n");
		return;
	}
	else
	{
		printf("The stack is:\n");
		for(int i=0;i<=s.top;i++)
			printf("%d ",s.stk[i]);
	}
	printf("\n");
	return;
}
int main(void)
{
	int option=1;
	int choice;
	s.top=-1;
	printf("Stack Operation.\n");
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
	
	
