#include "main.h"

void timer1_init(void)
{
	LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM1EN);
	/* Configure TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* Set divider:tDTS=tCK_INT  */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /* count mode：up count      */
  TIM1CountInit.Prescaler           = 24-1;                   /* clock prescaler：24     */
  TIM1CountInit.Autoreload          = 50-1;                   /* auto-reload value：50   */
  TIM1CountInit.RepetitionCounter   = 0;                        /* recount：0                */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* Enable output */
  LL_TIM_EnableAllOutputs(TIM1);
	/* Clear the update interrupt flag (UIF).  */
  LL_TIM_ClearFlag_UPDATE(TIM1);
  /*Enable update interrupt (UIE) */
  LL_TIM_EnableIT_UPDATE(TIM1);
	 /* Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);
	
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);

}

void timer1_pwm()
{
	LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* Set PA5/PB0/PA4 as TIM1_CH1/TIM1_CH2/TIM1_CH3 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_3;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
//TIM1CH1MapInit.Pin        = LL_GPIO_PIN_0;
//TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
//TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
//LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);
   
  /* Set PWM channel */
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM2;       /* channle mode：PWM2         */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;    /* Enable selected channle    */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH;   /* channle active level：high */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW;   /* channle idle polarity：low */
  /* CH1 compare value:250 */
  TIM_OC_Initstruct.CompareValue  = 250;
  /* Configure CH1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* CH2 compare value:500*/
  TIM_OC_Initstruct.CompareValue  = 500;
  /* Configure CH2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* CH3 compare value:750*/
  TIM_OC_Initstruct.CompareValue  = 750;
  /* Configure CH3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);

}


void timer14_init(void)
{
	LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM14EN);
	/* Configure TIM14 */
  LL_TIM_InitTypeDef TIM14CountInit = {0};
	
  TIM14CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* tDTS=tCK_IN                      */
  TIM14CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /* Counter used as upcounter        */
  TIM14CountInit.Prescaler           = 24-1;                   /* clock prescaler：8000            */
  TIM14CountInit.Autoreload          = 100-1;                   /* Autoreload value：3000           */
  TIM14CountInit.RepetitionCounter   = 0;                        /* Repetition counter value：0      */
  /* Initialize TIM14*/
  LL_TIM_Init(TIM14,&TIM14CountInit);
	
  /* Clear the update interrupt flag (UIF).  */
  LL_TIM_ClearFlag_UPDATE(TIM14);
  /*Enable update interrupt (UIE) */
  LL_TIM_EnableIT_UPDATE(TIM14);
  /*Enable TIM14 */
  LL_TIM_EnableCounter(TIM14);
  /*Enable UPDATE interrupt */
  NVIC_EnableIRQ(TIM14_IRQn);
  NVIC_SetPriority(TIM14_IRQn,1);

}

