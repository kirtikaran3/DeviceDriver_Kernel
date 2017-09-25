#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void signalhandler(int sig)
{
		printf("\nCaught ^C...Ouch.\n");
		signal(SIGINT,SIG_DFL);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, signalhandler);
	while(1)
	{
		printf("Program is running...\n");
		sleep(1);
	}
	return 0;
}
