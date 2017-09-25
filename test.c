#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void)
{
	printf("Enter a string.\n");
	char *s=NULL;
	int n=0;
	char c;
	while((c=fgetc(stdin))!='\n' && c!=EOF)
	{
		n++;
		s=(char *)realloc(s, sizeof(char)*(n+1));
		s[n-1]=c;
	}
	s[n]='\0';
	printf("String is %s\n",s);
	printf("Number of charcters is %zu.\n", strlen(s));	
	free(s);
	return 0;
}
