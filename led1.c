#include<wiringPi.h>
#include<pthread.h>
#include<errno.h>

void *writeled(void * p)
{
	pinMode((*(int *)p), OUTPUT);
	while(1)
	{
		digitalWrite((*(int *)p), HIGH);
		delay((*(int *)p)*100);
		digitalWrite((*(int *)p), LOW);
		delay((*(int *)p)*100);
	}
}

int main(void)
{
	wiringPiSetup();
	pthread_t thread1, thread2;
	int pm1=7;
	int pm2=22;
	int ret1=pthread_create(&thread1, NULL, writeled, (void *)&pm1);
	int ret2=pthread_create(&thread2, NULL, writeled, (void *)&pm2);
	if(ret1<0 || ret2<0)
	{
		perror("Faild to create thread.\n");
		return errno;
	}
	int retj1=pthread_join(thread1, NULL);
	int retj2=pthread_join(thread2, NULL);
	if(retj1<0 || retj2<0)
	{
		perror("Failed to join thread.\n");
		return errno;
	}
	return 0;
}