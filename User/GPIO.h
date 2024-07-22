#ifndef __GPIO_H
#define __GPIO_H
#include "main.h"










#define LED_1_PortClk   	 LL_IOP_GRP1_PERIPH_GPIOA
#define LED_1_Port   	 		 GPIOA
#define LED_1_Pin  		 		 LL_GPIO_PIN_0
#define LED_1_OFF  		 		 LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_0)
#define LED_1_ON  		 		 LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_0)



#ifdef KEY_USE
//KEY
	#define KEY_1_PortClk   	 LL_IOP_GRP1_PERIPH_GPIOA
	#define KEY_1_Port   	 		 GPIOA
	#define KEY_1_Pin  		 		 LL_GPIO_PIN_5
	#define KEY_1_Pull				 LL_GPIO_PULL_NO
	#define KEY_1_Exti				 LL_EXTI_LINE_5
	#define KEY_1_ExtiMode     LL_EXTI_TRIGGER_RISING_FALLING
	#define KEY_1_ExtiPort		 LL_EXTI_CONFIG_PORTA
	#define KEY_1_ExtiLine     LL_EXTI_CONFIG_LINE5
	#define KEY_1_ExtiIrqn		 EXTI4_15_IRQn
#endif

//MIC
#define MIC_1_PortClk      LL_IOP_GRP1_PERIPH_GPIOB
#define MIC_1_Port   	 		 GPIOB
#define MIC_1_Pin  		 		 LL_GPIO_PIN_1
#define MIC_1_Pull				 LL_GPIO_PULL_DOWN
#define MIC_1_Exti				 LL_EXTI_LINE_1
#define MIC_1_ExtiMode     LL_EXTI_TRIGGER_RISING_FALLING  //上升下降沿
#define MIC_1_ExtiPort		 LL_EXTI_CONFIG_PORTB
#define MIC_1_ExtiLine     LL_EXTI_CONFIG_LINE1
#define MIC_1_ExtiIrqn		 EXTI0_1_IRQn

//CHRG
#define CHRG_1_PortClk      LL_IOP_GRP1_PERIPH_GPIOA
#define CHRG_1_Port   	 		GPIOA
#define CHRG_1_Pin  		 		LL_GPIO_PIN_5
#define CHRG_1_Pull				  LL_GPIO_PULL_UP 
#define CHRG_1_Exti				  LL_EXTI_LINE_5
#define CHRG_1_ExtiMode     LL_EXTI_TRIGGER_RISING_FALLING  //上升下降沿
#define CHRG_1_ExtiPort		  LL_EXTI_CONFIG_PORTA
#define CHRG_1_ExtiLine     LL_EXTI_CONFIG_LINE5
#define CHRG_1_ExtiIrqn		  EXTI4_15_IRQn

//SWITCH
#define SWITCH_PortClk      LL_IOP_GRP1_PERIPH_GPIOB
#define SWITCH_Port   	 		GPIOB
#define SWITCH_Pin  		 		LL_GPIO_PIN_0
#define SWITCH_Pull				  LL_GPIO_PULL_NO
#define SWITCH_Exti				  LL_EXTI_LINE_0
#define SWITCH_ExtiMode     LL_EXTI_TRIGGER_RISING_FALLING  //上升下降沿
#define SWITCH_ExtiPort		  LL_EXTI_CONFIG_PORTB
#define SWITCH_ExtiLine     LL_EXTI_CONFIG_LINE0
#define SWITCH_ExtiIrqn		  EXTI0_1_IRQn





#define ADC_0_GPIO      LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG)
#define ADC_1_GPIO      LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_ANALOG)
#define ADC_2_GPIO      LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG)
#define ADC_3_GPIO      LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_ANALOG)
#define ADC_4_GPIO      LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_ANALOG)
#define ADC_5_GPIO      LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG)
#define ADC_6_GPIO      LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ANALOG)
#define ADC_7_GPIO      LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG)

void led_init(void);
void key_init(void);

void   Gpio_Init(void);


#endif
