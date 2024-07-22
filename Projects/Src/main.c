/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
extern void APP_SystemClockConfig(void);

/**
  * @brief  Application Entry Function.
  * @param  None
  * @retval int
  */

uint16_t a[3]={0};
uint8_t ADC_CHA[]={0,2,3};
uint8_t tim_flag=0;
uint8_t tim_10msflag=0;


u8   Test1;
u8   Test2;
u8   Test3;


__IO u32 Out_Oil_Time		__attribute__((at(0x20000A00)));		//油量计数器
__IO u8 Bat_Leve	__attribute__((at(0x20000A10)));		//电量
__IO u8 Oil_Leve __attribute__((at(0x20000A20)));		//油量
__IO u32 Short_Reset_Flag __attribute__((at(0x20000A30)));		//复位标志
__IO u32 Short_Reset_Flag1 __attribute__((at(0x20000A40)));		//复位标志



int main(void)
{
  // 时钟初始化，设置系统时钟为24M
  APP_SystemClockConfig();
 //	LL_mDelay(500);
	option_init();
	Gpio_Init();
	adc_init();
	iwdg_init();
	timer1_init();
	timer14_init();

	lptim_init();
	lptim_start();

	if(MIC_IO || ShortIsData())
	{
		OutInfo.Out_Enable_Flag = 1;
		SysInfo.systemState = SYSTEM_DILE;
		Disp_Short;
		SysInfo.Sleep_Time = 30;
	}else
	{
		Disp_Power_Rest;
		SysInfo.Power_Rest = 1;
		Out_Oil_Time = 0;
		Oil_Leve = 5;
		SysInfo.Power_Rest = 0;
		OutInfo.Out_Enable_Flag = 0;
		OutInfo.Out_Usb_In_Out_Smoke_Cnt = 0;
		SysInfo.systemState = SYSTEM_DILE;


		Get_Power_Rest_BatLeve();
		Get_Oil_Leve_Map();
		SysInfo.Sleep_Time = 30;
		SysInfo.Power_Rest = 0;
	}


	Switch_Init();
	Power_Reset_Port_Scan();

	ClrShortData();
//	Short_Reset_Flag = 0x00;
//	Short_Reset_Flag1 = 0x00;
	while (1)
	{
		Out_Deal();
		if(SysInfo._1ms_Flag)
		{
			SysInfo._1ms_Flag = 0;
			Switch_Scan();
		}

		if(SysInfo._10ms_Flag)
		{
			SysInfo._10ms_Flag = 0;
			LL_IWDG_ReloadCounter(IWDG);
			Port_Scan();
			DISP_Deal();
			//LedHand();

		}

		if(SysInfo._100ms_Flag)
		{
			SysInfo._100ms_Flag = 0;
			Get_Bat_Leve();
			Sleep();
		}
	}
}


/**
  * @brief  Error handling function
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file：Pointer to the source file name
  * @param  line：assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add His own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
