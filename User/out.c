#include "main.h"

OutInfoTypedef OutInfo;

void Get_Oil_Leve(void) // 100ms
{
  if (OUTLOAD)
  {
    if (Out_Oil_Time <= 742500)
    {
      if (swInfo.swGeras == SW_GERAS_L1)
      {
        Out_Oil_Time -= 30; // 0.1s
      }
      else if (swInfo.swGeras == SW_GERAS_L2)
      {
        Out_Oil_Time -= 50; // 0.1s
      }
      else
      {
        Out_Oil_Time -= 10;
      }
    }
  }
}

void Get_Oil_Leve_Map(void)
{
 u32 Temp;
 Temp = (u32)(Out_Oil_Time/7425);
 if(Temp >= 100)
 {
    Temp = 100;
 }
Oil_Leve = Temp;
if(Oil_Leve >=100)
{
  //Dispinfo.Disp_Data1 =     显示百分之一百
}
else if(Oil_Leve<100)
{
  if(Oil_Leve<10)
  {
    //Dispinfo.Disp)Data = 
  }
  else
  {
    //油量显示数据
  }
  //Dispinfo.Disp_Data = 油量数据

}



  OutInfo.Oil_Data_Map |= OIL_DISP_MASK;
}

void SetShortData(void)
{
  Short_Reset_Flag = 0x5555AAAA;
  Short_Reset_Flag1 = 0xAAAA5555;
}

void ClrShortData(void)
{
  Short_Reset_Flag = 0x00;
  Short_Reset_Flag1 = 0x00;
}

u8 ShortIsData(void)
{
  if ((Short_Reset_Flag == 0x5555AAAA) || (Short_Reset_Flag1 == 0xAAAA5555))
  {
    return 1;
  }

  return 0;
}

void Interrup_Ctr_Mos_Deal(void)
{

  if (OutInfo.Out_Mos_Interrup_Ctr_Flag)
  {

    if (OutInfo.Out_Pwm_Cycle < DUTY_MAX_VOLT)
    {
      OutInfo.Out_Pwm_Cycle++;
    }
    else
    {
      OutInfo.Out_Pwm_Cycle = 0;
    }

    if (OutInfo.Out_Pwm_Cycle <= OutInfo.Out_Pwm_Duty)
    {
      MOS_ON;
    }
    else
    {
      MOS_OFF;
    }

    if (OutInfo.Out_Pwm_Cycle == 5)
      OutInfo.Out_Duty_Main_Deal_Flag = 1;
  }

  if (OutInfo.Out_Mos_Interrup_Ctr_Flag1)
  {
    // 第二路
    if (OutInfo.Out_Pwm_Cycle1 < DUTY_MAX_VOLT)
    {
      OutInfo.Out_Pwm_Cycle1++;
    }
    else
    {
      OutInfo.Out_Pwm_Cycle1 = 0;
    }

    if (OutInfo.Out_Pwm_Cycle1 <= OutInfo.Out_Pwm_Duty1)
    {
      MOS1_ON;
    }
    else
    {
      MOS1_OFF;
    }

    if (OutInfo.Out_Pwm_Cycle1 == 5)
      OutInfo.Out_Duty_Main_Deal_Flag1 = 1;
  }
}

void Get_Out_Volt(void)
{
  OutInfo.Out_Adc_Volt = GetADCValue(OUT_CHANNEL);
  OutInfo.Out_Volt = (u32)OutInfo.Out_Adc_Volt * BatInfo.Bat_Volt >> 12;

  OutInfo.Out_Adc_Volt = GetADCValue(OUT1_CHANNEL);
  OutInfo.Out_Volt1 = (u32)OutInfo.Out_Adc_Volt * BatInfo.Bat_Volt >> 12;
}

void Out_Deal(void)
{
  u8 i = 0;

  if (OUTSTART)
  {
    CLR_OUTSTART;

    // 闪灯未结束是否可以抽吸 Disp_Smok_Error_Flag = 0 则本次闪灯结束前可以抽吸
    if (Dispinfo.Disp_Smok_Error_Flag == 0)
    {
      Dispinfo.Disp_Smok_Error_Flag = 0;
      Dispinfo.Disp_Num = 0;
      Dispinfo.Disp_Task = Idle;
    }

    if (!Dispinfo.Disp_Num && OutInfo.Out_Enable_Flag && SysInfo.systemState != SYSTEM_OFF)
    {
      Dispinfo.Disp_EN = 0; // 灭一下
      LL_GPIO_SetOutputPin(LED_PWR_EN_PORT, LED_PWR_EN_PIN);
      i = 250;
      while (i)
      {
        i--;
      }

      BatVoltage();

      Get_Bat_Leve_Map();
      Get_Oil_Leve_Map();

      //			 if(OutInfo.Out_Gear_Leve == 2){  ScanInfo.Gear_Data_Map = DISP_OUT_GEAR2;OutInfo.Set_Out_Volt = 3380;  }
      //			 else{ ScanInfo.Gear_Data_Map = DISP_OUT_GEAR1;OutInfo.Set_Out_Volt = 3000;}
      // if (OutInfo.Out_Usb_In_Out_Smoke_Cnt)
      // {
      //   OutInfo.Out_Usb_In_Out_Smoke_Cnt--;
      //   OutInfo.Set_Out_Volt = SET_USB_OUT_VOL;
      // }
      // else
      // {
      //   OutInfo.Set_Out_Volt = SET_OUT_VOL;
      // }

      if (BatInfo.Bat_Low_Lock)
      {
        BatInfo.Bat_Low_Lock = 1;
        Bat_Leve = 0;
        Disp_Bat_Low;
        return;
      }

      if (BatInfo.Bat_Volt <= BAT_START_OUT_LOW_VOL)
      {
        BatInfo.Bat_Low_Lock = 1;
        Bat_Leve = 0;
        Disp_Bat_Low;
        return;
      }

      //			 Short_Reset_Flag = 0xA5;
      //			 Short_Reset_Flag1 = 0x5A;

      if (BatInfo.Bat_Volt <= 4190)
      {
        BatInfo.Usb_Full_Flag = 0;
        BatInfo.Usb_Full_Cnt = 0;
        BatInfo.Usb_Disp_Long_Cnt = 0;

        if (USBIN)
        {
          BatInfo.Usb_In_Flag = 1;
        }
      }

      OutInfo.Out_Mos_Interrup_Ctr_Flag = 0;
      OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 0;
      Smok_Start_Bat_Leve_Deal();

      if (BatInfo.Bat_Low_Lock || (Bat_Leve == 0))
      {
        BatInfo.Bat_Low_Lock = 1;
        Bat_Leve = 0;
        Disp_Bat_Low;
        return;
      }

      OutInfo.Out_High_Res_Cnt = 0;
      // 第一路
      i = 50;
      MOS_ON;
      while (i)
      {
        i--;
      }
      OutInfo.Out_Adc_Volt = GetADCValue(OUT_CHANNEL);
      MOS_OFF;

      if (OutInfo.Out_Adc_Volt > 4080)
      {
        OutInfo.Out_High_Res_Cnt++;
      }

      // 延时再次采样，排除ADC异常值
      //			 i = 250;
      //			 while(i){i--;}
      delay_us(1000);

      i = 50;
      MOS_ON;
      while (i)
      {
        i--;
      }
      OutInfo.Out_Adc_Volt = GetADCValue(OUT_CHANNEL);
      MOS_OFF;

      if (OutInfo.Out_Adc_Volt > 4080)
      {
        OutInfo.Out_High_Res_Cnt++;
      }

      if (BatInfo.Bat_Volt <= 3600)
      {
        OutInfo.Short_Volt = 3950;
      } // 低阻值 0.7R 3980
      else
      {
        OutInfo.Short_Volt = 3970;
      }

      if (OutInfo.Out_Adc_Volt <= OutInfo.Short_Volt)
      {
        Disp_Short;
        return;
      }

      if (OutInfo.Out_High_Res_Cnt >= 2)
      {
        // 开路
        OutInfo.Out_High_Res_Cnt = 0;
        Disp_High;
        return;
      }

      OutInfo.Out_High_Res_Cnt = 0;
      // 第二路
      i = 50;
      MOS1_ON;
      while (i)
      {
        i--;
      }

      OutInfo.Out_Adc_Volt = GetADCValue(OUT1_CHANNEL);
      MOS1_OFF;

      if (OutInfo.Out_Adc_Volt > 4080)
      {
        OutInfo.Out_High_Res_Cnt++;
      }

      // 延时再次采样，排除ADC异常值
      //			 i = 250;
      //			 while(i){i--;}
      delay_us(1000);

      // 第二路
      i = 50;
      MOS1_ON;
      while (i)
      {
        i--;
      }

      OutInfo.Out_Adc_Volt = GetADCValue(OUT1_CHANNEL);
      MOS1_OFF;

      if (OutInfo.Out_Adc_Volt > 4080)
      {
        OutInfo.Out_High_Res_Cnt++;
      }

      if (OutInfo.Out_Adc_Volt <= OutInfo.Short_Volt)
      {
        Disp_Short;
        return;
      }

      if (OutInfo.Out_High_Res_Cnt >= 2)
      {
        // 开路
        Disp_High;
        return;
      }

      {
        // Dispinfo.Disp_Horse_Cnt = 0;
        OutInfo.Smok_Time = SMOKE_TIME_OUT;

        OutInfo.Bat_Low_Cnt = 0;

        if (swInfo.swGeras == SW_GERAS_L1)
        {
          if (OutInfo.Out_Mos_Ch_Change_Flag)
          {
            OutInfo.Out_Mos_Ch_Change_Flag = 0;

            OutInfo.Out_Pwm_Duty = DUTY_MAX_VOLT;
            OutInfo.Out_Pwm_Cycle = 0;

            OutInfo.Out_Pwm_Duty1 = 0;
            OutInfo.Out_Pwm_Cycle1 = 0;

            OutInfo.Out_Mos_Interrup_Ctr_Flag = 1;
            MOS_ON;

            OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 0;
            MOS1_OFF;
          }
          else
          {

            OutInfo.Out_Mos_Ch_Change_Flag = 1;

            OutInfo.Out_Pwm_Duty = 0;
            OutInfo.Out_Pwm_Cycle = 0;

            OutInfo.Out_Pwm_Duty1 = DUTY_MAX_VOLT;
            OutInfo.Out_Pwm_Cycle1 = 0;

            OutInfo.Out_Mos_Interrup_Ctr_Flag = 0;
            MOS_OFF;

            OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 1;
            MOS1_ON;
          }
        }
        else if (swInfo.swGeras == SW_GERAS_L2)
        {
          OutInfo.Out_Pwm_Duty = DUTY_MAX_VOLT;
          OutInfo.Out_Pwm_Cycle = 0;

          OutInfo.Out_Pwm_Duty1 = DUTY_MAX_VOLT;
          OutInfo.Out_Pwm_Cycle1 = 0;

          OutInfo.Out_Mos_Interrup_Ctr_Flag = 1;
          MOS_ON;

          OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 1;
          MOS1_ON;
        }

        //					Dispinfo.Disp_Smoke_Effect_Cnt =0;
        Dispinfo.Disp_Out_Delay = 2;
        LL_GPIO_ResetOutputPin(LED_PWR_EN_PORT, LED_PWR_EN_PIN);
        // 关充电电流
        CHRG_DISABLE;
        SetShortData();
        SET_OUTLOAD;
        // Dispinfo.Disp_Ic_Rgb_En = 1;
      }
    }
  }

  if (OUTLOAD)
  {
    if (!OutInfo.Smok_Time)
    {
      Disp_SmokOver;
      return;
    }

    if (OutInfo.Out_Mos_Interrup_Ctr_Flag)
    {
      if (OutInfo.Out_Short_Check_En_Flag)
      {
        // 检测短路
        OutInfo.Out_Adc_Volt = GetADCValue(OUT_CHANNEL);

        if (OutInfo.Out_Short_Check_En_Flag)
        {
          if (OutInfo.Out_Adc_Volt >= 500 && OutInfo.Out_Adc_Volt < 3300)
          {
            Disp_Short;
            return;
          }
        }
      }
    }

    if (OutInfo.Out_Mos_Interrup_Ctr_Flag1)
    {
      if (OutInfo.Out_Short_Check_En_Flag1)
      {
        // 检测短路
        OutInfo.Out_Adc_Volt = GetADCValue(OUT1_CHANNEL);

        if (OutInfo.Out_Short_Check_En_Flag1)
        {
          if (OutInfo.Out_Adc_Volt > 500 && OutInfo.Out_Adc_Volt < 3300)
          {
            Disp_Short;
            return;
          }
        }
      }
    }

    if (OutInfo.Out_Duty_Main_Deal_Flag == 1)
    {
      OutInfo.Out_Duty_Main_Deal_Flag = 0;

      BatVoltage();

      if (BatInfo.Bat_Volt <= BAT_OUT_LOW_VOL)
      {
        OutInfo.Bat_Low_Cnt++;
      }
      if (OutInfo.Bat_Low_Cnt >= 3)
      {
        Disp_Bat_Low;
        return;
      }

      Get_Out_Volt();

      OutInfo.Out_Pwm_Duty_Temp = (u32)OutInfo.Set_Out_Volt * 200ul / OutInfo.Out_Volt;

      if (OutInfo.Out_Pwm_Duty_Temp >= DUTY_MAX_VOLT)
      {
        OutInfo.Out_Pwm_Duty = DUTY_MAX_VOLT;
      }
      else if (OutInfo.Out_Pwm_Duty_Temp <= DUTY_MIN_VOLT)
      {
        OutInfo.Out_Pwm_Duty = DUTY_MIN_VOLT;
      }
      else
      {
#if OUT_RMS_EN
        OutInfo.Out_Pwm_Duty = OutInfo.Out_Pwm_Duty_Temp * OutInfo.Out_Pwm_Duty_Temp / DUTY_MAX_VOLT;
#else
        OutInfo.Out_Pwm_Duty = OutInfo.Out_Pwm_Duty_Temp;
#endif
      }
    }

    if (OutInfo.Out_Duty_Main_Deal_Flag1 == 1)
    {
      OutInfo.Out_Duty_Main_Deal_Flag1 = 0;

      BatVoltage();

      if (BatInfo.Bat_Volt <= BAT_OUT_LOW_VOL)
      {
        OutInfo.Bat_Low_Cnt++;
      }
      if (OutInfo.Bat_Low_Cnt >= 3)
      {
        Disp_Bat_Low;
        return;
      }

      Get_Out_Volt();

      OutInfo.Out_Pwm_Duty_Temp = (u32)OutInfo.Set_Out_Volt * 200ul / OutInfo.Out_Volt1;

      if (OutInfo.Out_Pwm_Duty_Temp >= DUTY_MAX_VOLT)
      {
        OutInfo.Out_Pwm_Duty = DUTY_MAX_VOLT;
      }
      else if (OutInfo.Out_Pwm_Duty_Temp <= DUTY_MIN_VOLT)
      {
        OutInfo.Out_Pwm_Duty = DUTY_MIN_VOLT;
      }
      else
      {
#if OUT_RMS_EN
        OutInfo.Out_Pwm_Duty1 = OutInfo.Out_Pwm_Duty_Temp * OutInfo.Out_Pwm_Duty_Temp / DUTY_MAX_VOLT;
#else
        OutInfo.Out_Pwm_Duty1 = OutInfo.Out_Pwm_Duty_Temp;
#endif
      }
    }
  }
  else
  {
    OutInfo.Out_Mos_Interrup_Ctr_Flag = 0;
    OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 0;
    MOS_OFF;
    MOS1_OFF;
  }
}
