#include <atom.h>
#include <util/delay.h>
#include "st7565r.h"
#include "lab4.h"
#include "SerialManager.h"

void ClearTask(int i)
{
	TaskBuffer[i]=NULL;
}
void ClearEvent(int i)
{
	EventBuffer[i].event=Empty;
}

void SC_fun(uint32_t data)
{
	unsigned int i=0;
	unsigned int j=0;
	while(1)
	{

		if(TaskBuffer[i]!=NULL && i<MAX_TASKS)
		{
			uint32_t Address=TaskBuffer[i]->entry_point;
			
			//Convert the address
			Address*=2;
			
			uint8_t Priority=TaskBuffer[i]->priority;
			uart_print("nT %p -p %ud\n",Address,Priority);
			ClearTask(i);	
		}
		switch(EventBuffer[j].event)
		{
			case ETaskPreempted:
			{
				uint32_t OldAddress=((TASK *)(EventBuffer[j].arg1))->entry_point;
				uint32_t NewAddress=((TASK *)(EventBuffer[j].arg2))->entry_point;
				OldAddress*=2;
				NewAddress*=2;
				uint32_t TimeStamp=EventBuffer[j].timestamp;
				uart_print("p %ul JP %p -t %p\n",TimeStamp,OldAddress,NewAddress);
				
			}break;
			case  ETaskArrived:
			{
				uint32_t Address=((TASK *)(EventBuffer[j].arg1))->entry_point;
				uint32_t TimeStamp=EventBuffer[j].timestamp;
				Address*=2;
				uart_print("p %ul JA %p\n",TimeStamp,Address);
			}break;
  			case ETaskResumed:
			{
				uint32_t Address=((TASK *)(EventBuffer[j].arg1))->entry_point;
				uint32_t TimeStamp=EventBuffer[j].timestamp;
				Address*=2;
				uart_print("p %ul JR %p\n",TimeStamp,Address);
			}break;
  			case ETaskCompleted:
			{
				uint32_t Address=((TASK *)(EventBuffer[j].arg1))->entry_point;
				uint32_t TimeStamp=EventBuffer[j].timestamp;
				Address*=2;
				uart_print("p %ul JC %p\n",TimeStamp,Address);
			}break;
			case EMutexCreated:
			{
				uint32_t MutexAddress=EventBuffer[j].arg1;
			//	MutexAddress*=2;
				uart_print("nM %p\n",MutexAddress);
			}break;
			case EMutexGetted:
			{
				uint32_t MutexAddress=EventBuffer[j].arg1;
			//	MutexAddress*=2;
				uint32_t JobAddress=((TASK *)(EventBuffer[j].arg2))->entry_point;
				JobAddress*=2;
				uint32_t TimeStamp=EventBuffer[j].timestamp;
				uart_print("p %ul AM %p %p\n",TimeStamp,MutexAddress,JobAddress);
			}break;
			case EMutexPutted:
			{
				uint32_t MutexAddress=EventBuffer[j].arg1;
			//	MutexAddress*=2;
				uint32_t JobAddress=((TASK *)(EventBuffer[j].arg2))->entry_point;
				JobAddress*=2;
				uint32_t TimeStamp=EventBuffer[j].timestamp;
				uart_print("p %ul RM %p %p\n",TimeStamp,MutexAddress,JobAddress);
			}break;
			default:
			{
				
			}break;

		}
		ClearEvent(j);
		i++;
		j++;

		if(i==MAX_TASKS)
		{
			i=0;
		}
		if(j>=MAX_EVENT)
		{
			j=0;
		}
		atomTimerDelay(1);
	}

}




