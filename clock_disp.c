#include <stdio.h>
#include <atom.h>
#include <util/delay.h>

#include "st7565r.h"
#include "lab4.h"

void clock_disp_func (uint32_t data)
{
//	TaskArrived(clock_disp_func);
	char *hello = "AtomClock v1.0";
	// Initialize LCD
	lcd_init();
	lcd_clear();

	// First draw title line at top row
	lcd_moveto(0,10);
	for (int i = 0 ; hello[i] != 0 ; i++)
		lcd_putc(hello[i]);
	// main display loop
	while(1) 
	{
	

		// Read global clock variables (protected by mutex lock)
		
		if (atomMutexGet(&clock_mutex, 0) == ATOM_OK) 
		{
			if(atomMutexGet(&lcd_mutex,0)==ATOM_OK)
			{
				lcd_moveto(2,30);
				lcd_putc('0' + g_hour / 10);
				lcd_putc('0' + g_hour % 10);
				lcd_putc(':');
				lcd_putc('0' + g_min / 10);
				lcd_putc('0' + g_min % 10);
				lcd_putc(':');
				lcd_putc('0' + g_sec / 10);
				lcd_putc('0' + g_sec % 10);
			}
			atomMutexPut(&lcd_mutex);
		}
		atomMutexPut(&clock_mutex);
		atomTimerDelay(10);
	}

}
