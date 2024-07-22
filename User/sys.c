#include "main.h"

SysInfoTypedef  SysInfo;


/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
void APP_SystemClockConfig(void)
{

	//使能相关时钟
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
		
  }

	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	//初始化1ms的滴答计时器
  LL_Init1msTick(24000000);
	//开启滴答中断
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
	//设置系统时间
  LL_SetSystemCoreClock(24000000);
}

void Sys_Init(void)
{
  //时钟初始化，设置系统时钟为24M
  APP_SystemClockConfig();
	//LL_mDelay(5000);
	LL_mDelay(500);
	option_init();
	Gpio_Init();
	timer1_init();
	adc_init();
	timer14_init();
}

