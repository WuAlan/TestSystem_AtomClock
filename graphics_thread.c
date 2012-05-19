#include <stdio.h>
#include <atom.h>
#include <util/delay.h>

#include "st7565r.h"
#include "lab4.h"

// Thread to draw a moving bar below the clock

void graphics_thread_func (uint32_t data)
{
	int c0 = 0;   // clear at this position
	int c1 = 40;  // fill at this position
	//atomTimerDelay(1000); // wait 1 sec to let clock_disp initialize LCD

	while(1) {
		if(atomMutexGet(&lcd_mutex,0)==ATOM_OK){
			lcd_moveto(4,c0);
			lcd_write(0);
			lcd_moveto(4,c1);
			lcd_write(0xff);

			c0++;
			if (c0 > 127)
				c0 = 0;
			c1++;
			if (c1 > 127)
				c1 = 0;
	//		_delay_ms(50); // busy wait 50 ms
	        
		}
		atomMutexPut(&lcd_mutex);		
		atomTimerDelay (5);  // wait 50 ms

	}
}
