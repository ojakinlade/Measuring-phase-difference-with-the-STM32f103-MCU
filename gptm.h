#ifndef _GPTM_H
#define _GPTM_H

#define GPTM_CLK_IN_8MHZ					8000000
#define GPTM_TIM_PRESCALE_8000		7999
#define GPTM_ENABLE								true
#define GPTM_DISABLE							false

extern void GPTM_Init(TIM_TypeDef* timerPort,
											uint16_t prescale,
											uint16_t reload, 
											bool interruptEn);

extern void GPTM_PWM_Init(TIM_TypeDef* timerPort, 
													uint16_t prescale,
													uint16_t reload,
													uint16_t dutyCycle);

extern void GPTM_Control(TIM_TypeDef* timerPort, bool timerEn);
extern uint16_t GPTM_Count_Value(TIM_TypeDef* timerPort);

#endif //_GPTM_H

