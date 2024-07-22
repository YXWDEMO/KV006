/**
  ******************************************************************************
  * @file    py32c642_it.c
  * @author  MCU Application Team
  * @brief   Interrupt Service Routines.
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

#define     LED_R         0XFF0000ul
#define     LED_G         0XFF00ul
#define     LED_B         0XFFul

#define     LED_Y         0XFFFF00ul
#define     LED_W         0XFFFFFFul


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "py32c642_it.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers         */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{         
	

	
}


void EXTI0_1_IRQHandler(void)
{
  /* Handle EXTI interrupt request */
  if(LL_EXTI_IsActiveFlag(LL_EXTI_LINE_0))
  {
    LL_EXTI_ClearFlag(LL_EXTI_LINE_0);
  }
	if(LL_EXTI_IsActiveFlag(LL_EXTI_LINE_1))
  {
    LL_EXTI_ClearFlag(LL_EXTI_LINE_1);
  }
}


void EXTI2_3_IRQHandler(void)
{
  /* Handle EXTI interrupt request */
  if(LL_EXTI_IsActiveFlag(LL_EXTI_LINE_2))
  {
    LL_EXTI_ClearFlag(LL_EXTI_LINE_2);
  }

	if(LL_EXTI_IsActiveFlag(LL_EXTI_LINE_3))
  {
    LL_EXTI_ClearFlag(LL_EXTI_LINE_3);
  }
}


void EXTI4_15_IRQHandler(void)
{
  /* Handle EXTI interrupt request */
  if(LL_EXTI_IsActiveFlag(LL_EXTI_LINE_4))
  {
    LL_EXTI_ClearFlag(LL_EXTI_LINE_4);
  }

	if(LL_EXTI_IsActiveFlag(LL_EXTI_LINE_5))
  {
    LL_EXTI_ClearFlag(LL_EXTI_LINE_5);
  }
}

extern uint8_t tim_flag;


void TIM14_IRQHandler(void)
{
	if((LL_TIM_ReadReg(TIM14,SR) & LL_TIM_SR_UIF) == 1 && LL_TIM_IsEnabledIT_UPDATE(TIM14))
  {
    LL_TIM_ClearFlag_UPDATE(TIM14);
    tim_flag++;

//		控制MOS开关
//		Interrup_Ctr_Mos_Deal();

   if(OutInfo.Out_Mos_Interrup_Ctr_Flag)
   {
			if(OutInfo.Out_Pwm_Duty == 0)
			{
					CLR_OUTLOAD;
					OutInfo.Out_Pwm_Cycle = 0;
					OutInfo.Out_Short_Check_En_Flag = 0;
					MOS_OFF;
			}else
			{
				if(OutInfo.Out_Pwm_Cycle < DUTY_MAX_VOLT){OutInfo.Out_Pwm_Cycle++;}
				else{OutInfo.Out_Pwm_Cycle  = 0;}

				if(OutInfo.Out_Pwm_Cycle < OutInfo.Out_Pwm_Duty){MOS_ON;}
				else{MOS_OFF;}
				
				if(OutInfo.Out_Pwm_Cycle == 8)
						OutInfo.Out_Duty_Main_Deal_Flag = 1;

				if(OutInfo.Out_Pwm_Cycle > 1 && OutInfo.Out_Pwm_Cycle < (OutInfo.Out_Pwm_Duty - 1))
				{
					OutInfo.Out_Short_Check_En_Flag = 1;
				} else
				{
					OutInfo.Out_Short_Check_En_Flag = 0;
				}
			}
	 }

   if(OutInfo.Out_Mos_Interrup_Ctr_Flag1)
	 {

			if(OutInfo.Out_Pwm_Duty1 == 0)
			{
					CLR_OUTLOAD;
					OutInfo.Out_Pwm_Cycle1 = 0;
					OutInfo.Out_Short_Check_En_Flag1 = 0;
					MOS1_OFF;
			}else
			{
					//第二路
					if(OutInfo.Out_Pwm_Cycle1 < DUTY_MAX_VOLT){OutInfo.Out_Pwm_Cycle1++;}
					else{OutInfo.Out_Pwm_Cycle1  = 0;}
					

					if(OutInfo.Out_Pwm_Cycle1 < OutInfo.Out_Pwm_Duty1){MOS1_ON;}
					else{MOS1_OFF;}

					if(OutInfo.Out_Pwm_Cycle1 == 8)
						OutInfo.Out_Duty_Main_Deal_Flag1 = 1;
			 
					if(OutInfo.Out_Pwm_Cycle1 > 1 && OutInfo.Out_Pwm_Cycle1 < (OutInfo.Out_Pwm_Duty1 - 1)){
						OutInfo.Out_Short_Check_En_Flag1 = 1;
					}else{
						OutInfo.Out_Short_Check_En_Flag1 = 0;
					}
			}
			
		}

	if(SysInfo.Time_1ms < 10){SysInfo.Time_1ms++;}
   else
   {
     SysInfo.Time_1ms = 1;
	   SysInfo._1ms_Flag = 1;

		 if(SysInfo.Time_10ms < 10){SysInfo.Time_10ms++;}
		 else
		 {
				SysInfo.Time_10ms = 1;
				SysInfo._10ms_Flag = 1;
				
				
			 
				if(SysInfo.Time_100ms < 10)
				{
						SysInfo.Time_100ms++;
				}
				else
				{
						 SysInfo.Time_100ms = 1;
						 SysInfo._100ms_Flag = 1;
						 Get_Oil_Leve();
						//Horse_Run_Deal();
						if(OutInfo.Smok_Time){OutInfo.Smok_Time--;}
						if(SysInfo.Sleep_Time){SysInfo.Sleep_Time--;}
				}

		 }

		}   

	// 显示驱动
	// Disp_Drive();
// 	Dispinfo.sys_led_display_isr_cnt++;

// 	if(Dispinfo.sys_led_display_isr_cnt >= 1)
// 	{
// 	   Dispinfo.sys_led_display_isr_cnt = 0;
// 		 PIN1_IN;PIN2_IN;PIN3_IN;PIN4_IN;
// //	 PIN5_IN;PIN6_IN;PIN7_IN;PIN8_IN;

// 	   if(Dispinfo.Disp_EN == 0)
// 		 { 
// 		     Dispinfo.Disp_offset = 0;			   
// 		 }
// 		 else
// 		 {
// 		   switch(Dispinfo.Disp_offset)
// 			 {
// 		//第一组数据		 
// 				 case 0:
// 				 {
// 							if(Dispinfo.Disp_Data & c_bit_0){  PIN1_L;PIN2_H;}
// 							if(Dispinfo.Disp_Data & c_bit_1){  PIN1_L;PIN3_H;}
// 							if(Dispinfo.Disp_Data & c_bit_2){  PIN1_L;PIN4_H;}
// 				 }
// 				 break;

// 				 case 1:
// 				 {
// 				     if(Dispinfo.Disp_Data & c_bit_3){  PIN2_L;PIN1_H;}
// 				     if(Dispinfo.Disp_Data & c_bit_4){  PIN2_L;PIN3_H;}
// 				     if(Dispinfo.Disp_Data & c_bit_5){  PIN2_L;PIN4_H;}
// 				 }
// 				 break;

// 				 case 2:
// 				 {
// 				   if(Dispinfo.Disp_Data & c_bit_6){  PIN3_L;PIN1_H;}
// 				   if(Dispinfo.Disp_Data & c_bit_7){  PIN3_L;PIN2_H;}
// 				   if(Dispinfo.Disp_Data & c_bit_8){ PIN3_L;PIN4_H;}
// 				 }
// 				 break;

// 				 case 3:
// 				 {
// 				   if(Dispinfo.Disp_Data & c_bit_9){ PIN4_L;PIN1_H;}
// 					 if(Dispinfo.Disp_Data & c_bit_10){ PIN4_L;PIN2_H;}
// 					 if(Dispinfo.Disp_Data & c_bit_11){ PIN4_L;PIN3_H;}
// 				 }
// 			   break;

// 			 }

// 			 if(Dispinfo.Disp_offset < 4){Dispinfo.Disp_offset++;}else{Dispinfo.Disp_offset = 0;}

// 		 }

// 	}

  }
}


//50us

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
	if((LL_TIM_ReadReg(TIM1,SR) & LL_TIM_SR_UIF) == 1 && LL_TIM_IsEnabledIT_UPDATE(TIM1))
  {
    LL_TIM_ClearFlag_UPDATE(TIM1);
    //tim_flag++;
		// IC幻彩灯显示处理
		// LED_Ic_Handle();
  }
}

/******************************************************************************/
/* PY32C642 Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
