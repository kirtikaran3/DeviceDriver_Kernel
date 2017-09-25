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
int c=0;
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
	c++;
	return;
}
void Append(void)
{
	if(c==0)
	{
		Insert();
		return;
	}
	int p;
	printf("Enter the position, that must be less than or equal to %d, where it must be entered.\n",c);
	scanf("%d",&p);
	if(p>c||p==0)
	{
		printf("Incorrect position.\n");
		return;
	}
	else if(p==1)
	{
		Insert();
		return;
	}
	int d;
	printf("Enter the data to be inserted.\n");
	scanf("%d",&d);	
	NODE * temp=head;
	NODE * t;
	while(p!=2)
	{
		temp=head->next;
		p--;
	}
	NODE * new = (NODE *) malloc(sizeof(NODE));
	new->data=d;
	t=temp->next;
	temp->next=new;
	new->next=t;
	c++;
	return;
}
int DeleteTail(void)
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
	printf("The delete data is %d. Deleted from the end of the linked list.\n",d);
	c--;
	return d;
}
int DeleteHead(void)
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
	t=head->next;
	d=head->data;
	head=t;
	t->prev=head;
	printf("The delete data is %d. Deleted from the beginning of the linked list.\n",d);
	c--;
	return d;
}	
int Remove(void)
{
	int p;
	int d;
	printf("Enter the position, that must be less than or equal to %d, where it must be entered.\n",c);
	scanf("%d",&p);
	if(p>c || p==0)
	{
		printf("Incorrect Position.\n");
		return -1;
	}
	else if(head==NULL || head==tail || p==c)
	{
		d = DeleteTail();
		return d;
	}
	else if(p==1)
	{
		d=DeleteHead();
		return d;
	}
	NODE * t=head;
	NODE * temp;
	while(p!=2)
	{
		t=head->next;
		p--;
	}
	temp=t->next;
	t->next=temp->next;
	temp->next->prev=t;
	d=temp->data;
	printf("The delete data is %d.\n",d);
	c--;
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
		printf("2--Delete (at End) an Element.\n");
		printf("3--Delete (at Beginning) an Element.\n");
		printf("4--Append an Element.\n");
		printf("5--Remove an Element.\n");	
		printf("6--Display the List.\n");
		printf("Enter your choice.\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				Insert();
				break;
			case 2:
				DeleteTail();
				break;
			case 3:
				DeleteHead();
				break;
			case 4:
				Append();
				break;
			case 5:
				Remove();
				break;
			case 6:
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
