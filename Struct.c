#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct Student
{
	char *name;
	int size;
	int rollNo;
	float marks;
};
void input(struct Student *s)
{
	char n[40];	
	printf("Enter a name.\n");
	fgets(n,40,stdin);
	s->size=strlen(n);
	s->name=(char *)malloc(sizeof(char)*(s->size+1));
	strcpy(s->name,n);
	s->name[s->size]='\0';
	printf("Enter the Roll Number.\n");
	scanf("%d",&s->rollNo);
	printf("Enter the Marks of the Student.\n");
	scanf("%f",&s->marks);
}
void output(struct Student *s)
{
	printf("The name of the student is: ");
	fputs(s->name,stdout);
	printf("The roll number of the student is: %d\n",s->rollNo);
	printf("The marks of the student is: %.2f\n",s->marks);
}
int main(void)
{
	struct Student s;
	input(&s);
	output(&s);
	return 0;
}
