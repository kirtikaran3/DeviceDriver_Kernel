#include<wiringPi.h>
//#include<pthreads.h>

int main(void)
{
	wiringPiSetup();
	pinMode(7, OUTPUT);
	while(1)
	{
		digitalWrite(7, HIGH);
		delay(1000);
		digitalWrite(7, LOW);
		delay(1000);
	}
	return 0;
}