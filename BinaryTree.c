#include<stdio.h>
#include<malloc.h>
#include<math.h>
typedef struct Node
{
	int data;
	struct Node *l;
	struct Node *r;
} Node;
Node *root=NULL;
int c=-1;
void Insert(void)
{
	int d;
	printf("Enter data to be inserted.\n");
	scanf("%d",&d);
	Node *new = (Node *) malloc(sizeof(Node));
	if(root==NULL)
	{
		root=new;
		c++;
		return;
	}
	Node *t=root;
	int m=(int)pow(2,c);
	while(m!=0)
	{
		if(t->l!=NULL)
			m--;
		else
			t->l=new;
	}
	if(m==0)
	{
		m=(int)pow(2,c);
		t=root;
	}
	while(m!=0)
	{
		if(t->r!=NULL)
			m--;
		else
			t->r=new;	
	}
}
void Display(void)
{
	Node *t=root;
	while(t->l!=NULL)
	{
		printf("%d ",t->data);
		t=t->l;
	}
	t=root->r;
	if(t==NULL)
		return;
	while(t->r!=NULL)
	{
		printf("%d ",t->data);
	}
}	
int main(void)
{
	int choice=1;
	int option;
	while(choice)
	{	
		Insert();
		Display();
		printf("Do you want to continue (0 or 1) ?\n");
		scanf("%d", &choice);
	}
	return 0;
}
