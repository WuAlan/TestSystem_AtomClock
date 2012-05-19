#include <stdio.h>
#include <atom.h>
#include <util/delay.h>

#include "st7565r.h"
#include "lab4.h"
#include "StopWatch.h"
#define Button (0.1*SYSTEM_TICKS_PER_SEC) // update clock on LCD 10 times/sec
void UpdateMin();
void Update(uint8_t button,uint8_t data);
uint8_t ButtonDown(uint8_t button);
void button_thread_func(uint32_t data)
{
	DDRK = 0x00; // port K (buttons) marked as inputs
	PORTK = 0xff; // enable pull-up on port K
	DDRL = 0xff; // port L (leds) marked as outputs
	uint8_t timeout=0;
	uint8_t button=0;
	char state = 'W'; // W = waiting, D = down, C = confirmed, R=repeated
	// loop forever serving button presses
	while (1) {


		button=PINK;
		switch (state)
		{
			case 'W':
			{	
				if (ButtonDown(button)==1) 
				{
					state = 'D';
					timeout=0;
				}

			}break;
			case 'D':
			{
				timeout++;
				if (ButtonDown(button)==0) 
				{
					state = 'W';
				}
				if (timeout==2) {
				 	state = 'C';
					Update(button,data);
					timeout=0;
				}	
			}break;
			case 'C':
			{
				timeout++;
				if (ButtonDown(button)==0) 
				{
					state = 'W';
				}			
				else if(timeout==80)
				{
					state='R';
					timeout=0;
				}
			}break;
			case 'R':
			{
				timeout++;
				if(timeout==20)
				{
					timeout=0;
					Update(button,data);
				}			
				else if (ButtonDown(button)==0) 
				{
					state = 'W';
				}
			}break;

		
		}

		atomTimerDelay(1);		
	//	_delay_ms(1000);

	}
}

void UpdateMin()
{
	g_min++;
	if (g_min > 59)
	{
		g_min = 0;
	}
}

void UpdateSec()
{
		g_sec++;
		if (g_sec > 59) 
		{
			g_sec = 0;
		}
}

void UpdateHour()
{
	g_hour++;
	if (g_hour > 23)
		g_hour = 0;
}

void Update(uint8_t button,uint8_t data)
{
	if((button&0x01)==0&&data==1)
	{
		UpdateHour();
	}
	else if((button&0x02)==0&&data==2)
	{
		UpdateMin();
	}
	else if((button&0x04)==0&&data==4)
	{
		UpdateSec();
	}
}

uint8_t ButtonDown(uint8_t button)
{
	if((button & 0x01)==0||(button & 0x02)==0||(button & 0x04)==0)
		return 1;
	return 0;
}
