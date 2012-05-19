#include <util/delay.h>
#include "SerialManager.h"
#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
int main( void )
{
	SerialInit(MYUBRR);
	while(1)
	{
		_delay_ms(10000);
		SendString("LAB");
	}

	
}
