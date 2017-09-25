#include<stdio.h>
#include<malloc.h>
struct Node
{
	int data;
	struct Node *next;
};
typedef struct Node NODE;
NODE * llist = NULL;
int c=0;
void Insert(void)
{
	int d;
	printf("Enter the data to be inserted in front of the linked list.\n");
	scanf("%d",&d);
	NODE * new = (NODE *)malloc(sizeof(NODE));
	new->data=d;
	if(llist==NULL)
	{
		new->next=NULL;
		llist=new;
	}
	else
	{
		new->next=llist;
		llist=new;
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
	NODE * temp=llist;
	NODE * t;
	while(p!=2)
	{
		temp=llist->next;
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
int Delete(void)
{
	if(llist==NULL)
	{
		printf("Linked List is empty.\n");
		return -1;
	}
	int d;
	NODE * temp;
	temp=llist;
	d=llist->data;
	llist=llist->next;
	printf("The deletion occured at the front of the linked list. The value was %d\n",d);
	c--;
	return d;
}
void Display(void)
{
	NODE * temp;
	temp=llist;
	if(temp==NULL)
	{
		printf("Linked List is Empty.\n");
		return;
	}
	while(temp->next!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("%d ",temp->data);
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
		printf("3--Append an Element.\n");	
		printf("4--Display the List.\n");
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
				Append();
				break;
			case 4:
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
