// Our thread functions (except main thread)

void clock_disp_func (uint32_t data);
void clock_update_func (uint32_t data);
void graphics_thread_func (uint32_t data);
void button_thread_func (uint32_t data);
void SC_fun(uint32_t data);


#include <atommutex.h>
#include "Tracer.h"
#include "StopWatch.h"

// Variables defined in main_thread.c

extern ATOM_MUTEX clock_mutex;
extern ATOM_MUTEX lcd_mutex;
extern uint8_t g_hour, g_min, g_sec;
