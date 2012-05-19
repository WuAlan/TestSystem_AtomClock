#include <stdio.h>
#include <atom.h>

#include "lab4.h"
#include "uart.h"

/* STDIO stream to make printf work on uart output */
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

#define STACK_SIZE_BYTES 204

// Priorities, lower number is higher priority, main thread runs at priority 16
#define CLOCK_DISP_PRIO      18
#define CLOCK_UPDATE_PRIO    17
#define GRAPHICS_THREAD_PRIO 19
#define Button_Thread_PRIO 16
#define SC_Thread_PRIO 250


static ATOM_TCB clock_disp_tcb;
static ATOM_TCB clock_update_tcb;
static ATOM_TCB graphics_tcb;
static ATOM_TCB button_tcb;
static ATOM_TCB SC_tcb;


static uint8_t clock_disp_stack[STACK_SIZE_BYTES];
static uint8_t clock_update_stack[STACK_SIZE_BYTES];
static uint8_t graphics_stack[STACK_SIZE_BYTES];
static uint8_t button_stack[STACK_SIZE_BYTES];
static uint8_t SC_stack[STACK_SIZE_BYTES];

// Mutex for single-threaded access to global clock variables
ATOM_MUTEX clock_mutex;
ATOM_MUTEX lcd_mutex;
// Global variables to hold clock
uint8_t g_hour = 0, g_min = 0, g_sec = 0;

/**
 * \b main_thread_func
 *
 * Entry point for main application thread.
 *
 * This is the first thread that will be executed when the OS is started.
 *
 * @param[in] data Unused (optional thread entry parameter)
 *
 * @return None
 */
void main_thread_func (uint32_t data)
{
    int8_t status = 0;
	int8_t lcd_status=0;
	/* Create a mutex for single-threaded access to global clock variables */
	status = atomMutexCreate (&clock_mutex);
	lcd_status=atomMutexCreate(&lcd_mutex);

    stdout = &uart_stdout;

	if (status == ATOM_OK)
	{
		// Create the clock display thread
	    status = atomThreadCreate(&clock_disp_tcb,
	                 CLOCK_DISP_PRIO, clock_disp_func, 0,
	                 &clock_disp_stack[0],
	                 STACK_SIZE_BYTES,
	                 FALSE);
	}
	if (status == ATOM_OK)
	{
		// Create the clock update thread
	    status = atomThreadCreate(&clock_update_tcb,
	                 CLOCK_UPDATE_PRIO, clock_update_func, 0,
	                 &clock_update_stack[0],
	                 STACK_SIZE_BYTES,
	                 FALSE);
	}
    if (status == ATOM_OK)
    {
			status = atomThreadCreate(&button_tcb,
      	             Button_Thread_PRIO, button_thread_func, 1,
                     &button_stack[0],
                     STACK_SIZE_BYTES,
                     FALSE);			

    }

	if(status==ATOM_OK)
	{
		status = atomThreadCreate(&graphics_tcb,
                     GRAPHICS_THREAD_PRIO, graphics_thread_func, 0,
                     &graphics_stack[0],
                     STACK_SIZE_BYTES,
                     FALSE);
	}
	if(status==ATOM_OK)
	{
		status = atomThreadCreate(&SC_tcb,
                     SC_Thread_PRIO, SC_fun, 0,
                     &SC_stack[0],
                     STACK_SIZE_BYTES,
                     FALSE);
	}
	// All threads created ok: run the main loop of the main thread
	while (1)
	{
		atomTimerDelay (2 * SYSTEM_TICKS_PER_SEC); // wait 2 sec
	}
	

}
