#include <stdio.h>
#include <atom.h>
#include <util/delay.h>

#include "lab4.h"


void clock_update_func (uint32_t data)
{
	while(1) {
		// Increment time (global variables protected by mutex lock)
		if (atomMutexGet(&clock_mutex, 0) == ATOM_OK) {

			g_sec++;
			if (g_sec > 59) {
				g_sec = 0;
				g_min++;
				if (g_min > 59) {
					g_min = 0;
					g_hour++;
					if (g_hour > 23)
						g_hour = 0;
				}
			}
			
		}
		atomMutexPut(&clock_mutex);
		atomTimerDelay(100);

	}
}
