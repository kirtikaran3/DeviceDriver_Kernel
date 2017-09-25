#include<stdio.h>
#include<malloc.h>
struct Node
{
	int data;
	struct Node *next;
	struct Node *prev;
};
typedef struct Node NODE;
NODE *head=NULL;
NODE *tail=NULL;
void Insert(void)
{
	int d;
	printf("Enter the data to be inserted.\n");
	scanf("%d",&d);
	NODE * new = (NODE *) malloc ( sizeof(NODE) );
	new->data=d;
	if(head==NULL)
	{
		head=new;
		tail=new;
	}
	else
	{
		new->prev=tail;
		tail->next=new;
		new->next=NULL;
		tail=new;
	}
	return;
}
int Delete(void)
{
	if(head==NULL)
	{
		printf("Linked List is empty.\n");
		return -1;
	}
	int d;
	if(head==tail)
	{
		d=head->data;
		head=tail=NULL;
		return d;
	}
	NODE * t;
	t=tail->prev;
	d=tail->data;
	t->next=NULL;
	tail=t;
	printf("The delete data is %d. Delted from the end of the linked list.\n",d);
	return d;
}
void Display(void)
{
	if(head==NULL)
	{
		printf("Linked List is empty.\n");
		return;
	}
	NODE * t=head;
	while(t->next!=NULL)
	{
		printf("%d ",t->data);
		t=t->next;
	}
	printf("%d ",t->data);
	printf("\n");
	return;
}
int main(void)
{
	int option=1;
	int choice;
	while(option)
	{
		printf("1--Insert an Element.\n");
		printf("2--Delete an Element.\n");	
		printf("3--Display the List.\n");
		printf("Enter your choice.\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				Insert();
				break;
			case 2:
				Delete();
				break;
			case 3:
				Display();
				break;
			default:
				return 0;
		}
		printf("Do you want to continue (Enter 0 or 1) ?\n");
		scanf("%d",&option);
	}
	return 0;
}
