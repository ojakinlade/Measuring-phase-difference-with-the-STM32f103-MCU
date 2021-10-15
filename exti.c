#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "exti.h"
#include "gpio.h"
#include "systick.h"

#define NUMBER_OF_EXTI_LINES		5

static volatile bool edgeDetected[ NUMBER_OF_EXTI_LINES ];
static volatile uint32_t count_v;
static volatile uint32_t count_c;
static volatile bool flag = false;



void EXTI_Init(uint8_t extIntLine, bool edgeTrigger)
{
	/*
	Description:
	
	Parameters:
	1.)extIntLine
	
	2.)edgeTrigger: if this parameter is passed 'EXTI_RISING_EDGE' or 'true',
	the rising trigger is enabled otherwise if passed 'EXTI_FALLING_EDGE'
	or 'false', the falling trigger is enabled.
	
	Return:
	
	*/
	EXTI->IMR |= (1<<extIntLine); //unmask EXT interrupt line
	
	if (edgeTrigger)
	{
		EXTI->RTSR |= (1<<extIntLine); //enable rising trigger for EXT interrupt line
	}
	
	else
	{
		EXTI->FTSR |= (1<<extIntLine); //enable falling trigger for EXT interrupt line
	}
	
}

void EXTI_Set_Edge_Detected(uint8_t extIntLine, bool isDetected)
{
	edgeDetected[extIntLine] = isDetected;
}

bool EXTI_Get_Edge_Detected(uint8_t extIntLine)
{
	return edgeDetected[extIntLine];
}

bool EXTI_Get_Flag_Status(void)
{
	return flag;
}

void EXTI_Set_Flag_Status(bool status)
{
	flag = status;
}


void EXTI_Get_Voltage_Count_Value(uint32_t* timestamp)
{
	*timestamp = count_v;
	
}

void EXTI_Get_Current_Count_Value(uint32_t* timestamp)
{
	*timestamp = count_c;

}


void EXTI0_IRQHandler(void)
{
	if ( (EXTI->PR & EXTI_PR_PR0) == EXTI_PR_PR0 )
	{
		EXTI->PR |= EXTI_PR_PR0; //clear pending register bit
	}
//	if(GPIO_Input_Read(GPIOA, GPIO_PIN0))
//	{
//		count_v1 = SysTick_GetTick();
//	}
//	
//	else
//	{
//		count_v2 = SysTick_GetTick();
//		edgeDetected[EXTI_LINE0] = true;
//	}
	if(!flag)
	{
		count_v = SysTick_GetTick();
	}
	
}

void EXTI4_IRQHandler(void)
{
	if ( (EXTI->PR & EXTI_PR_PR4) == EXTI_PR_PR4 )
	{
		EXTI->PR |= EXTI_PR_PR4; //clear pending register bit
	}
//	if(GPIO_Input_Read(GPIOA, GPIO_PIN4))
//	{
//		count_c1 = SysTick_GetTick();
//	}
//	
//	else
//	{
//		count_c2 = SysTick_GetTick();
//		edgeDetected[EXTI_LINE4] = true;
//	}
	if(!flag)
	{
		count_c = SysTick_GetTick();
		flag = true;
	}
	
}
	
