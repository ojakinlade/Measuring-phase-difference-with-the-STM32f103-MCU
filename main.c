#include <stdbool.h>
#include <stdint.h>
#include "system.h"
#include "lm358.h"

typedef struct
{
	uint32_t count;
	
}data_t;

data_t current = {0};
data_t voltage = {0};

double phase_diff;


int main(void)
{
	System_Init();
	voltage_Init();
	current_Init();
	
	while(1)
	{
		if(get_Flag_Status())
		{
			get_Voltage_Timer_Value(&voltage.count);
			get_Current_Timer_Value(&current.count);
			
			if(voltage.count > current.count)
			{
				phase_diff = ((voltage.count - current.count)/20.0) * 360.0;
				
			}
			else
			{
				phase_diff = ((current.count - voltage.count)/20.0) * 360.0;
			}
			
			
			reset_Flag_Status();
			
		}
	}
}
