#include "main.h"

extern void delay_us(uint16_t us);

void lptim_init(void)
{
	
	LL_LPTIM_InitTypeDef LPTIM_InitStruct = {0};
	 /* Set wake-up mode of the LPTIM(EXTI Line29) to event request */
  LL_EXTI_DisableIT(LL_EXTI_LINE_29);   /* Disable interrupt request for EXTI Line29 */
  LL_EXTI_EnableEvent(LL_EXTI_LINE_29); /* Enable event request for EXTI Line29 */
	
	/* Enabel LSI */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }

  /* Select LSI as LTPIM clock source */
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE_LSI);

  /* Enable LPTIM clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
	
	/* Initialize LPTIM */
  LPTIM_InitStruct.Prescaler = LL_LPTIM_PRESCALER_DIV128;        /* prescaler: 128 */
  LPTIM_InitStruct.UpdateMode = LL_LPTIM_UPDATE_MODE_IMMEDIATE;  /* registers are updated after each APB bus write access */
  if (LL_LPTIM_Init(LPTIM, &LPTIM_InitStruct) != SUCCESS)
  {
    APP_ErrorHandler();
  }
}


void lptim_start(void)
{
//	/* Enable LPTIM1 interrupt */
//  NVIC_SetPriority(LPTIM1_IRQn, 0);
//  NVIC_EnableIRQ(LPTIM1_IRQn);

  /* Enable LPTIM autoreload match interrupt  */
  LL_LPTIM_EnableIT_ARRM(LPTIM);

  /* Enable LPTIM */
  LL_LPTIM_Enable(LPTIM);

  /* Set autoreload value */
  LL_LPTIM_SetAutoReload(LPTIM, 512);				// 2S

  /* LPTIM starts in single mode */
  LL_LPTIM_StartCounter(LPTIM, LL_LPTIM_OPERATING_MODE_ONESHOT);
	
	LPTIM->ICR |= 1<<1;//clear ARRMCF bit
	
	delay_us(150);
	
}

