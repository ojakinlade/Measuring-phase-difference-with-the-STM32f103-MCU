#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include "gpio.h"
#include "afio.h"
#include "exti.h"
#include "lm358.h"



void voltage_Init(void)
{
	/*PA0 GPIO configuration*/
	GPIO_Input_Init(GPIOA,
									GPIO_PORT_REG_LOW,
									GPIO_PIN0,
									GPIO_PIN0_INPUT_FLOATING,
									false);
	
	/*AFIO configuration for PA0*/
	AFIO_Init(EXTI_LINE0, AFIO_EXTI_SELECT_PA0);
	/*EXTI configuration for PA0*/
	EXTI_Init(EXTI_LINE0, EXTI_RISING_EDGE);
	//EXTI_Init(EXTI_LINE0, EXTI_FALLING_EDGE);
	/*EXTI interrupt enable*/
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void current_Init(void)
{
	/*PA4 GPIO config*/
	GPIO_Input_Init(GPIOA,
									GPIO_PORT_REG_LOW,
									GPIO_PIN4,
									GPIO_PIN4_INPUT_FLOATING,
									false);
	/*AFIO configuration for PA4*/
	AFIO_Init(EXTI_LINE4, AFIO_EXTI_SELECT_PA4);
	/*EXTI configuration for PA4*/
	EXTI_Init(EXTI_LINE4, EXTI_RISING_EDGE);
	//EXTI_Init(EXTI_LINE4, EXTI_FALLING_EDGE);
	/*EXTI interrupt enable*/
	NVIC_EnableIRQ(EXTI4_IRQn);
	
}


void get_Voltage_Timer_Value(uint32_t* V)
{
	EXTI_Get_Voltage_Count_Value(V);
}

void get_Current_Timer_Value(uint32_t* C)
{
	EXTI_Get_Current_Count_Value(C);

}



bool get_Flag_Status(void)
{
	return EXTI_Get_Flag_Status();
}

void reset_Flag_Status(void)
{
	EXTI_Set_Flag_Status(false);
}


