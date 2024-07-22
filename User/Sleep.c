#include "main.h"


void Gpio_Wake(void);

void   Sleep_Gpio(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
//	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
//	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
	/*******************GPIOA GPIOB GPIOF ALL pin config PULL DN INPUT*************************/	
	GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	LL_GPIO_ResetOutputPin(GPIOC,LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7);

//		 LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_ALL,LL_GPIO_MODE_INPUT);
//		 LL_GPIO_SetPinPull(GPIOC,LL_GPIO_PIN_ALL,LL_GPIO_PULL_DOWN);
	
   //MOS	
	   LL_GPIO_SetOutputPin(MOS_PORT,MOS_PIN);             //输出高
	   LL_GPIO_SetOutputPin(MOS1_PORT,MOS1_PIN);             //输出高      
   	 LL_GPIO_SetOutputPin(LED_PWR_EN_PORT,LED_PWR_EN_PIN);

//输出端
	   LL_GPIO_SetPinMode(HEAT_PORT,HEAT_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(HEAT_PORT,HEAT_PIN,LL_GPIO_PULL_DOWN);

//		 LL_GPIO_SetPinMode(HEAT1_PORT,HEAT1_PIN,LL_GPIO_MODE_ANALOG);
//		 LL_GPIO_SetPinPull(HEAT1_PORT,HEAT1_PIN,LL_GPIO_PULL_DOWN);

		 LL_GPIO_SetPinMode(HEAT1_PORT,HEAT1_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(HEAT1_PORT,HEAT1_PIN,LL_GPIO_PULL_DOWN);

//		 LL_GPIO_SetPinMode(HEAT1_PORT,HEAT1_PIN,LL_GPIO_MODE_ANALOG);
//		 LL_GPIO_SetPinPull(HEAT1_PORT,HEAT1_PIN,LL_GPIO_PULL_DOWN);

#ifdef KEY_USE
  	 LL_GPIO_SetPinMode(KEY_PORT, KEY_PIN, LL_GPIO_MODE_INPUT);
#endif

// LED IC
		 // LED IC PWR DISABLE
	   LL_GPIO_SetPinMode(LED_PWR_EN_PORT, LED_PWR_EN_PIN, LL_GPIO_MODE_OUTPUT);     
	   LL_GPIO_SetPinOutputType(LED_PWR_EN_PORT, LED_PWR_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL); 
		 LL_GPIO_SetPinSpeed(LED_PWR_EN_PORT,LED_PWR_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

//	   LL_GPIO_SetPinMode(LED_SING_PORT,LED_SING_PIN,LL_GPIO_MODE_INPUT);
//		 LL_GPIO_SetPinPull(LED_SING_PORT,LED_SING_PIN,LL_GPIO_PULL_DOWN);

		// LED IC OUTPUT LOW
   	 LL_GPIO_ResetOutputPin(LED_SING_PORT,LED_SING_PIN);                 
	   LL_GPIO_SetPinMode(LED_SING_PORT, LED_SING_PIN, LL_GPIO_MODE_OUTPUT);     
	   LL_GPIO_SetPinOutputType(LED_SING_PORT, LED_SING_PIN, LL_GPIO_OUTPUT_PUSHPULL); 
		 LL_GPIO_SetPinSpeed(LED_SING_PORT,LED_SING_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

//数码管
     PIN1_L;PIN2_L;PIN3_L;PIN4_L;
//		 PIN1_IN;PIN2_IN;PIN3_IN;PIN4_IN;
//		 PIN5_L;PIN6_L;PIN7_L;PIN8_L;
//MIC
     LL_GPIO_SetPinMode(MIC_PORT,MIC_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(MIC_PORT,MIC_PIN,LL_GPIO_PULL_DOWN);

//USB IN
     LL_GPIO_SetPinMode(USB_PORT,USB_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(USB_PORT,USB_PIN,LL_GPIO_PULL_NO);

//CHRG
     LL_GPIO_SetPinMode(CHRG_PORT,CHRG_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(CHRG_PORT,CHRG_PIN,LL_GPIO_PULL_UP);

		 // CHRG EN
     LL_GPIO_SetPinMode(CHRG_EN_PORT,CHRG_EN_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(CHRG_EN_PORT,CHRG_EN_PIN,LL_GPIO_PULL_NO);

//SWITCH
     LL_GPIO_SetPinMode(SWITCH_DIP_PORT,SWITCH_DIP_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(SWITCH_DIP_PORT,SWITCH_DIP_PIN,LL_GPIO_PULL_NO);

     LL_GPIO_SetPinMode(SWITCH_DIP_EN_PORT,SWITCH_DIP_EN_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(SWITCH_DIP_EN_PORT,SWITCH_DIP_EN_PIN,LL_GPIO_PULL_UP);

	   LL_GPIO_SetPinMode(MOS_PORT, MOS_PIN, LL_GPIO_MODE_OUTPUT);
		 LL_GPIO_SetPinSpeed(MOS_PORT, MOS_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);
	   LL_GPIO_SetPinOutputType(MOS_PORT, MOS_PIN, LL_GPIO_OUTPUT_PUSHPULL); 


	   LL_GPIO_SetPinMode(MOS1_PORT, MOS1_PIN, LL_GPIO_MODE_OUTPUT);
	   LL_GPIO_SetPinSpeed(MOS1_PORT, MOS1_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);
		 LL_GPIO_SetPinOutputType(MOS1_PORT, MOS1_PIN, LL_GPIO_OUTPUT_PUSHPULL); 

//		 LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_INPUT);//CLK
//		 LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);//DAT
		 LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_NO);
		 LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);

//   	 LL_GPIO_ResetOutputPin(SWITCH_DIP_EN_PORT,SWITCH_DIP_EN_PIN);
//	   LL_GPIO_SetPinMode(SWITCH_DIP_EN_PORT, SWITCH_DIP_EN_PIN, LL_GPIO_MODE_OUTPUT);     
//	   LL_GPIO_SetPinOutputType(SWITCH_DIP_EN_PORT, SWITCH_DIP_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL); 
//		 LL_GPIO_SetPinSpeed(SWITCH_DIP_EN_PORT,SWITCH_DIP_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);
		 //
#ifdef KEY_USE
  LL_EXTI_InitTypeDef EXTI_InitStruct={0};
	//
	EXTI_InitStruct.Line = KEY_1_Exti;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = KEY_1_ExtiMode;
  LL_EXTI_Init(&EXTI_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(KEY_1_ExtiPort,KEY_1_ExtiLine);
	//使能中断
	NVIC_SetPriority(KEY_1_ExtiIrqn, 0);
  NVIC_EnableIRQ(KEY_1_ExtiIrqn);
#endif

	
  LL_EXTI_InitTypeDef EXTI1_InitStruct={0};

	EXTI1_InitStruct.Line = MIC_1_Exti;
  EXTI1_InitStruct.LineCommand = ENABLE;
  EXTI1_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI1_InitStruct.Trigger = MIC_1_ExtiMode;
  LL_EXTI_Init(&EXTI1_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(MIC_1_ExtiPort,MIC_1_ExtiLine);
	//使能中断
	NVIC_SetPriority(MIC_1_ExtiIrqn, 0);
  NVIC_EnableIRQ(MIC_1_ExtiIrqn);
	

	LL_EXTI_InitTypeDef EXTI2_InitStruct={0};

	EXTI2_InitStruct.Line = CHRG_1_Exti;
  EXTI2_InitStruct.LineCommand = ENABLE;
  EXTI2_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI2_InitStruct.Trigger = CHRG_1_ExtiMode;
  LL_EXTI_Init(&EXTI2_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(CHRG_1_ExtiPort,CHRG_1_ExtiLine);
	//使能中断
	NVIC_SetPriority(CHRG_1_ExtiIrqn, 0);
  NVIC_EnableIRQ(CHRG_1_ExtiIrqn);

	EXTI2_InitStruct.Line = SWITCH_Exti;
  EXTI2_InitStruct.LineCommand = ENABLE;
  EXTI2_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI2_InitStruct.Trigger = SWITCH_ExtiMode;
  LL_EXTI_Init(&EXTI2_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(SWITCH_ExtiPort,SWITCH_ExtiLine);
	//使能中断
	NVIC_SetPriority(SWITCH_ExtiIrqn, 0);
  NVIC_EnableIRQ(SWITCH_ExtiIrqn);

}

u8 mic_bit_temp=0;
u8 usb_bit_temp=0;
u8 usb_ad_bit_temp=0;
u8 switch_bit_temp=0;

u8 mic_bit_temp1=0;
u8 usb_bit_temp1=0;
u8 usb_ad_bit_temp1=0;
u8 switch_bit_temp1=0;

void enter_stop(void)
{	
	LL_TIM_DisableCounter(TIM1);
	LL_TIM_DisableCounter(TIM14);
	
  LL_TIM_ClearFlag_UPDATE(TIM1);
  LL_TIM_DisableIT_UPDATE(TIM1);

  LL_TIM_ClearFlag_UPDATE(TIM14);
  LL_TIM_DisableIT_UPDATE(TIM14);
	
	LL_APB1_GRP2_DisableClock(RCC_APBENR2_TIM1EN);
	LL_APB1_GRP2_DisableClock(RCC_APBENR2_TIM14EN);
	
	Get_Usb_Ad();

	if(BatInfo.Usb_Ad_Volt >= 700)
	{
		usb_ad_bit_temp = 1;
	}
	else
	{
		usb_ad_bit_temp = 0;
	}
	
	adc_disable();
//	SET_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST); // ADC复位
//	CLEAR_BIT(RCC->APBRSTR2, RCC_APBRSTR2_ADCRST); // ADC 释放复位

	LL_IWDG_ReloadCounter(IWDG);	//喂狗

	Sleep_Gpio();
	
	if(MIC_IO)
	{
		mic_bit_temp=1;
	}
  else
	{		
		mic_bit_temp=0;	
	}

	if(CHRG_IO)	
	{
		usb_bit_temp=1;
	}
	else
	{
		usb_bit_temp=0;
	}

	if(SWITCH_IO)
	{
	  switch_bit_temp=1;
	}
	else
	{
		switch_bit_temp=0;
	}

LPTIM_SLEEP:
	adc_disable();
	lptim_start();
	//关闭滴答中断
	CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
  /* STOP mode with low power regulator ON */
  LL_PWR_SetLprMode(LL_PWR_LPR_MODE_LPR);
  /* SRAM retention voltage aligned with digital LDO output */
  LL_PWR_SetStopModeSramVoltCtrl(LL_PWR_SRAM_RETENTION_VOLT_CTRL_LDO);
  /* Enter DeepSleep mode */
  LL_LPM_EnableDeepSleep();
  /* Request Wait   */
   __SEV();
   __WFE();
   __WFE();
  LL_LPM_EnableSleep();
	//开启滴答中断
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);

	LL_IWDG_ReloadCounter(IWDG);

	if(1)
	{
		if(MIC_IO)
		{
			mic_bit_temp1=1;
		}
		else
		{		
			mic_bit_temp1=0;
		}

		if(CHRG_IO)	
		{
			usb_bit_temp1=1;
		}
		else
		{
			usb_bit_temp1=0;
		}

		if(SWITCH_IO)
		{
			switch_bit_temp1=1;
		}
		else
		{
			switch_bit_temp1=0;
		}

		BatVoltage();
		Get_Usb_Ad();

		if(BatInfo.Usb_Ad_Volt >= 700)
		{
			usb_ad_bit_temp1 = 1;
		}
		else
		{
			usb_ad_bit_temp1 = 0;
		}

		if((usb_ad_bit_temp!=usb_ad_bit_temp1)||(mic_bit_temp!=mic_bit_temp1) ||(usb_bit_temp!=usb_bit_temp1)||(switch_bit_temp!=switch_bit_temp1) || (BatInfo.Usb_Full_Flag&&(BatInfo.Bat_Volt < 4050)))
		{
			if(BatInfo.Usb_Full_Flag&&(BatInfo.Bat_Volt < 4050))
			{
				BatInfo.Usb_Full_Flag = 0;
			}
		}
		else
		{
			goto LPTIM_SLEEP;
		}
	}

	// 开启定时器时钟
	LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM1EN);
	LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM14EN);

	// 开启定时器中断
  LL_TIM_ClearFlag_UPDATE(TIM1);
  LL_TIM_EnableIT_UPDATE(TIM1);

  LL_TIM_ClearFlag_UPDATE(TIM14);
  LL_TIM_EnableIT_UPDATE(TIM14);

	// 使能定时器
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_EnableCounter(TIM14);

}


void   Sleep(void)
{
   if(Dispinfo.Disp_Num||OUTLOAD|| (USBIN && (!(BatInfo.Usb_Full_Flag&&(!BatInfo.Usb_Disp_Long_Cnt)))) ||BatInfo.Bat_Leve_Delay_Cnt){SysInfo.Sleep_Time = 30;}
	 else if(!SysInfo.Sleep_Time)
	 {

		  if(SysInfo.Power_Rest)
			{
			  SysInfo.Power_Rest  = 0;
			  Get_Power_Rest_BatLeve();
			}

	    Dispinfo.Disp_Horse_Cnt = 0; 
	    OutInfo.Out_Mos_Interrup_Ctr_Flag = 0;
			OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 0;
			MOS_OFF;MOS1_OFF;

	    enter_stop();

			Gpio_Wake();
			LL_EXTI_DisableRisingTrig(SWITCH_Exti);
			LL_EXTI_DisableRisingTrig(MIC_1_Exti);
			LL_EXTI_DisableRisingTrig(CHRG_1_Exti);
			LL_EXTI_DisableFallingTrig(SWITCH_Exti);
			LL_EXTI_DisableFallingTrig(MIC_1_Exti);
			LL_EXTI_DisableFallingTrig(CHRG_1_Exti);

			SysInfo.Sleep_Time = 30;

	 }

}

/*==============================================================================
*函数名    : Gpio_Wake
*函数功能  : GPIO唤醒初始化函数
*函数参数  : void
*函数返回值: void
*函数描述  : 
==============================================================================*/
void Gpio_Wake(void)
{

	LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM1EN);
	LL_APB1_GRP2_EnableClock(RCC_APBENR2_TIM14EN);
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_EnableCounter(TIM14);
	
//MOS	
	   LL_GPIO_SetOutputPin(MOS_PORT,MOS_PIN);             //输出高
	   LL_GPIO_SetPinMode(MOS_PORT, MOS_PIN, LL_GPIO_MODE_OUTPUT);
	   LL_GPIO_SetPinOutputType(MOS_PORT, MOS_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	   LL_GPIO_SetOutputPin(MOS1_PORT,MOS1_PIN);             //输出高     
	   LL_GPIO_SetPinMode(MOS1_PORT, MOS1_PIN, LL_GPIO_MODE_OUTPUT);
	   LL_GPIO_SetPinOutputType(MOS1_PORT, MOS1_PIN, LL_GPIO_OUTPUT_PUSHPULL);


//输出端检测   直接模拟口
	   LL_GPIO_SetPinMode(HEAT_PORT,HEAT_PIN,LL_GPIO_MODE_ANALOG);
		 LL_GPIO_SetPinPull(HEAT_PORT, HEAT_PIN, LL_GPIO_PULL_NO);
	   LL_GPIO_SetPinMode(HEAT1_PORT,HEAT1_PIN,LL_GPIO_MODE_ANALOG);
		 LL_GPIO_SetPinPull(HEAT1_PORT, HEAT1_PIN, LL_GPIO_PULL_NO);

#ifdef KEY_USE
  	 LL_GPIO_SetPinMode(KEY_PORT, KEY_PIN, LL_GPIO_MODE_INPUT);
#endif

//LED IC PWR EN
   	 LL_GPIO_ResetOutputPin(LED_PWR_EN_PORT,LED_PWR_EN_PIN);// 低使能
	   LL_GPIO_SetPinMode(LED_PWR_EN_PORT, LED_PWR_EN_PIN, LL_GPIO_MODE_OUTPUT);
	   LL_GPIO_SetPinOutputType(LED_PWR_EN_PORT, LED_PWR_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL);
		 LL_GPIO_SetPinSpeed(LED_PWR_EN_PORT,LED_PWR_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

//LED IC  输出低
   	 LL_GPIO_ResetOutputPin(LED_SING_PORT,LED_SING_PIN);
	   LL_GPIO_SetPinMode(LED_SING_PORT, LED_SING_PIN, LL_GPIO_MODE_OUTPUT);
	   LL_GPIO_SetPinOutputType(LED_SING_PORT, LED_SING_PIN, LL_GPIO_OUTPUT_PUSHPULL);
		 LL_GPIO_SetPinSpeed(LED_SING_PORT,LED_SING_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

// SWITCH DIP
   	LL_GPIO_ResetOutputPin(SWITCH_DIP_EN_PORT,SWITCH_DIP_EN_PIN);
	  LL_GPIO_SetPinMode(SWITCH_DIP_EN_PORT, SWITCH_DIP_EN_PIN, LL_GPIO_MODE_OUTPUT);
	  LL_GPIO_SetPinOutputType(SWITCH_DIP_EN_PORT, SWITCH_DIP_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(SWITCH_DIP_EN_PORT,SWITCH_DIP_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

		LL_GPIO_SetPinMode(SWITCH_DIP_PORT,SWITCH_DIP_PIN,LL_GPIO_MODE_ANALOG);


//数码管
     PIN1_IN;PIN2_IN;PIN3_IN;PIN4_IN;
//		 PIN5_IN;PIN6_IN;PIN7_IN;PIN8_IN;

//MIC
     LL_GPIO_SetPinMode(MIC_PORT,MIC_PIN,LL_GPIO_MODE_INPUT);


//USB IN
     LL_GPIO_SetPinMode(USB_PORT,USB_PIN,LL_GPIO_MODE_ANALOG);
		 LL_GPIO_SetPinPull(USB_PORT, USB_PIN, LL_GPIO_PULL_NO);

//CHRG
     LL_GPIO_SetPinMode(CHRG_PORT,CHRG_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(CHRG_PORT,CHRG_PIN,LL_GPIO_PULL_UP);

//CHRG EN
   	CHRG_ENABLE;
	  LL_GPIO_SetPinMode(CHRG_EN_PORT, CHRG_EN_PIN, LL_GPIO_MODE_OUTPUT);
	  LL_GPIO_SetPinOutputType(CHRG_EN_PORT, CHRG_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(CHRG_EN_PORT,CHRG_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

//	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);//CLK
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_DOWN);
//	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);//DAT
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);
	
}


