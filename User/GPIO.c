#include "GPIO.h"
#include "main.h"


void led_init(void)
{	
	#if 0	
	//使能GPIO时钟
  LL_IOP_GRP1_EnableClock(LED_1_PortClk);
	//设置IO为输出模式
  LL_GPIO_SetPinMode(LED_1_Port, LED_1_Pin, LL_GPIO_MODE_OUTPUT);
	//设置IO为推挽输出
  LL_GPIO_SetPinOutputType(LED_1_Port, LED_1_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	//设置IO速度
  LL_GPIO_SetPinSpeed(LED_1_Port, LED_1_Pin, LL_GPIO_SPEED_FREQ_LOW); 
	//设置IO为浮空
  LL_GPIO_SetPinPull(LED_1_Port, LED_1_Pin, LL_GPIO_PULL_NO); 

	#endif
	  /* Enable GPIOA clock  */
  LL_IOP_GRP1_EnableClock(LED_1_PortClk);

  /* Configure PA1 pin in output push-pull mode to drive external LEDs */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = LED_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_1_Port, &GPIO_InitStruct);

}

void key_init(void)
{
#ifdef KEY_USE
	//使能GPIO时钟
  LL_IOP_GRP1_EnableClock(KEY_1_PortClk);
	//设置IO为输入模式
  LL_GPIO_SetPinMode(KEY_1_Port, KEY_1_Pin, LL_GPIO_MODE_INPUT);
	//设置IO为上拉
  LL_GPIO_SetPinPull(KEY_1_Port, KEY_1_Pin, KEY_1_Pull);
#endif
  
#ifdef KEY_USE
  LL_EXTI_InitTypeDef EXTI_InitStruct={0};
	//下降沿触发
	EXTI_InitStruct.Line = KEY_1_Exti;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = KEY_1_ExtiMode;
  LL_EXTI_Init(&EXTI_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(KEY_1_ExtiPort,KEY_1_ExtiLine);
#endif

	//使能GPIO时钟
  LL_IOP_GRP1_EnableClock(MIC_1_PortClk);
	//设置IO为输入模式
  LL_GPIO_SetPinMode(MIC_1_Port, MIC_1_Pin, LL_GPIO_MODE_INPUT);
	//设置IO为上拉
  LL_GPIO_SetPinPull(MIC_1_Port, MIC_1_Pin, MIC_1_Pull);
	
	//使能GPIO时钟
  LL_IOP_GRP1_EnableClock(MIC_1_PortClk);
	//设置IO为输入模式
  LL_GPIO_SetPinMode(CHRG_1_Port, CHRG_1_Pin, LL_GPIO_MODE_INPUT);
	//设置IO为上拉
  LL_GPIO_SetPinPull(CHRG_1_Port, CHRG_1_Pin, MIC_1_Pull);
	
  LL_EXTI_InitTypeDef EXTI_InitStruct={0};

	EXTI_InitStruct.Line = MIC_1_Exti;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = MIC_1_ExtiMode;
  LL_EXTI_Init(&EXTI_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(MIC_1_ExtiPort,MIC_1_ExtiLine);

	EXTI_InitStruct.Line = CHRG_1_Exti;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = CHRG_1_ExtiMode;
  LL_EXTI_Init(&EXTI_InitStruct);
	//触发源
  LL_EXTI_SetEXTISource(CHRG_1_ExtiPort,CHRG_1_ExtiLine);
	
	//使能中断
//	NVIC_SetPriority(KEY_1_ExtiIrqn, 0);
//  NVIC_EnableIRQ(KEY_1_ExtiIrqn);
}


void   Gpio_Init(void)
{
//	  GPIOA->MODER = 0x0000FFEFUL;
//	  GPIOB->MODER = 0x0000EFFFUL;
//	  GPIOC->MODER = 0x0000000FUL;

//	  GPIOB->OSPEEDR = 0x00003000UL;

//	  GPIOA->PUPDR  = 0x00000020UL;
//	  GPIOB->PUPDR  = 0x00001000UL;

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_ALL);//开启  GPIO ABC全部时钟
//	  LL_IOP_GRP1_EnableClock(LED_1_PortClk);
//  	LL_IOP_GRP1_EnableClock(LED_1_PortClk);
	  //PA7  MOS    PA6  输出检测  PA5  触摸按键   PA4  USB    PA3  DI时序灯    PA2  TX    PA1  PA0  PB0-PB5 数码管    PB6 SW    PB7  MIC   PC1  CHRG  PC0  RST

//MOS	
	   LL_GPIO_SetOutputPin(MOS_PORT,MOS_PIN);             //输出高
	   LL_GPIO_SetOutputPin(MOS1_PORT,MOS1_PIN);             //输出高    
   	 LL_GPIO_ResetOutputPin(LED_PWR_EN_PORT,LED_PWR_EN_PIN);// 低使能

//		 delay_us(1000);

#ifdef KEY_USE
  	 LL_GPIO_SetPinMode(KEY_PORT, KEY_PIN, LL_GPIO_MODE_INPUT);
#endif

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
		 LL_GPIO_SetPinPull(MIC_PORT,MIC_PIN,LL_GPIO_PULL_DOWN);


//USB IN
     LL_GPIO_SetPinMode(USB_PORT,USB_PIN,LL_GPIO_MODE_ANALOG);
		 LL_GPIO_SetPinPull(USB_PORT,USB_PIN,LL_GPIO_PULL_NO);

//CHRG
     LL_GPIO_SetPinMode(CHRG_PORT,CHRG_PIN,LL_GPIO_MODE_INPUT);
		 LL_GPIO_SetPinPull(CHRG_PORT,CHRG_PIN,LL_GPIO_PULL_UP);

//CHRG EN
   	CHRG_ENABLE;
	  LL_GPIO_SetPinMode(CHRG_EN_PORT, CHRG_EN_PIN, LL_GPIO_MODE_OUTPUT);
	  LL_GPIO_SetPinOutputType(CHRG_EN_PORT, CHRG_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(CHRG_EN_PORT,CHRG_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

//LED IC PWR EN
	   LL_GPIO_SetPinMode(LED_PWR_EN_PORT, LED_PWR_EN_PIN, LL_GPIO_MODE_OUTPUT);
	   LL_GPIO_SetPinOutputType(LED_PWR_EN_PORT, LED_PWR_EN_PIN, LL_GPIO_OUTPUT_PUSHPULL);
		 LL_GPIO_SetPinSpeed(LED_PWR_EN_PORT,LED_PWR_EN_PIN,LL_GPIO_SPEED_FREQ_VERY_HIGH);

	  LL_GPIO_SetPinMode(MOS_PORT, MOS_PIN, LL_GPIO_MODE_OUTPUT);
	  LL_GPIO_SetPinOutputType(MOS_PORT, MOS_PIN, LL_GPIO_OUTPUT_PUSHPULL);
 
	  LL_GPIO_SetPinMode(MOS1_PORT, MOS1_PIN, LL_GPIO_MODE_OUTPUT);
	  LL_GPIO_SetPinOutputType(MOS1_PORT, MOS1_PIN, LL_GPIO_OUTPUT_PUSHPULL);

//输出端检测   直接模拟口
	   LL_GPIO_SetPinMode(HEAT_PORT,HEAT_PIN,LL_GPIO_MODE_ANALOG);
	   LL_GPIO_SetPinMode(HEAT1_PORT,HEAT1_PIN,LL_GPIO_MODE_ANALOG);

//		 LL_GPIO_ResetOutputPin(GPIOC,LL_GPIO_PIN_0);             //输出低     
//	   LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);     
//	   LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_0, LL_GPIO_OUTPUT_PUSHPULL); 
 
}









