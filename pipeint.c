#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
int main(int argc, char *argv[])
{
	int fd[2],ret;
	pid_t pid;
	char buf[100];
	ret=pipe(fd);
	if(ret<0)
	{
		printf("Failed to create a pipe.\n");
		exit(0);
	}
	else
	{
		pid=fork();
		if(pid<0)
		{
			printf("Failed to fork.\n");
			exit(0);
		}
		else
		{
			if(pid==0)
			{
				printf("Child Process...\n");
				read(fd[0],buf,100);
				int n=strlen(buf);
				int a[n/2];
				int i=0;
				int j=0;
				for(i=0, j=0;i<n/2;i++,j+=2)
				{
					a[i]=(int)buf[j]-48;
				}
				printf("Operands are:\n");
				for(int i=0;i<n/2;i++)
				{
					printf("%d ",a[i]);
				}
				int s=0;
				for(int i=0;i<n/2;i++)
				{
					s+=a[i];
				}
				printf("Sum is %d\n",s);
				int d,r,p=s;
				d=p/10;
				i=0;
				while(d!=0)
				{
					r=p%10;
					buf[i]=(char)(r+48);
					p=d;
					d=p/10;
					i++;
				}
				buf[i]='\0';
				strrev(buf);
				write(fd[1],buf,100);
				printf("Child writes %d\n",s);
			}
			else
			{
				printf("Parent Process...\n");
				printf("Enter a series of single digit intergers seperated by spaces.\n");
				fgets(buf,100,stdin);
				write(fd[1],buf,100);
				printf("Parent writes %s\n",buf);
				wait(NULL);
				printf("Parent Process...\n");
				read(fd[0],buf,100);
				int n=strlen(buf);
				int a[n/2];
				int j=0;
				int i=0;
				for(i=0,j=0;i<n/2;i++,j+=2)
				{
					a[i]=(int)buf[j]-48;
				}
				int s=0;
				for(int i=0;i<n/2;i++)
				{
					s=s*10+a[i];
				}
				printf("Parent Reads %d",s);
			}
		}
	}
	return 0;
}
