#include "main.h"

#define DELAY_COEFFICIENT 1 // 延迟系数

#define F_CPU 24000000UL // 24 MHz

#define LED_H                     \
  {                               \
    GPIOA->BSRR |= LL_GPIO_PIN_0; \
  }
#define LED_L                    \
  {                              \
    GPIOA->BRR |= LL_GPIO_PIN_0; \
  } //  LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_3);}

// 一个高 360NS
#define _0_CODE \
  {             \
    LED_H;      \
    LED_L;      \
  }
#define _1_CODE \
  {             \
    LED_H;      \
    LED_H;      \
    LED_L;      \
  }

void delay(u16 us)
{
  while (us--)
    ; // 500ns
}

Dispinfotypedef Dispinfo;

// //发送位
// void  send_bit(u8 bit_val)
// {

//   if(bit_val)//1
//   {

// 	  _1_CODE;

// 	}
// 	else//0
// 	{
// 	  _0_CODE;

// 	}

// }

// //发送字节
// void  send_byte(u32 byte_val)
// {

//   u8 i;

// 	u8  data;

// 	for(i=0;i<24;i++)
//   {

// 	  send_bit((byte_val &(0x800000>>i))!=0);

// 	}

// //	data = 0xff;
// //	for(i=0;i<8;i++)
// //  {
// //
// //	  send_bit((data &(0x80>>i))!=0);
// //
// //	}

// }

// ////发送颜色
// //void  send_color(u8 Color)
// //{

// //  send_byte(Color);

// //}

// //更新灯带
// void  updata_led_strip(void)
// {
//   LED_L;
// //	delay(DELAY_COEFFICIENT*30);

// }

// //low  低电平时间
// //hig  高电平时间
// //Yard_mode：码元类型
// //0:0码    0码                  低电平时间  0.9us   高电平时间  0.3us
// //1:1码                         低电平时间  0.6us   高电平时间  0.6us
// //其他：rest码                   最小200us电平

// void   Led_Test(u32  Data)
// {
// //	u8 i = 19;

// //	while(i--)
// //	{
// 		send_byte(Data);
// //	}

// //	updata_led_strip();

// //	delay(200);

// }

// void   Clr_Led(void)
// {
//   u8 i;

// 	for(i = 0;i< 28;i++)
// 	{
// 	  send_byte(0x000000);

// 	}

// }
void Set_Breath_Num(u8 num,u8 lm,u8 count,u8 map)
{
  Set_Breath_Num = num;
  Breath_Count = count;
  Breath_LM = lm;
  Breath_Cycle = 0;
  if(Breath_LM == 0)
   {
     Breath_Duty = 0;
   }
   Breath_En = 1;
   //Led_Map = map;
}

void Breath_Deal(void)
{
  if (Breath_En)
  {
    if (Breath_Cycle < Breath_Count){Breath_Cycle++;}
    else
    {
      Breath_Cycle = 0;

      if (Breath_LM == 0) // 渐亮
      {
        if (Breath_Duty < Breath_Count)
        {
            Breath_Duty++;
        }
        else
        {
          if (Breath_Num)
          {
            Breath_LM = 1;
          }
          else
          {
            Breath_En = 0;
          }
        }
      }
      else
      {
        if (Breath_Duty > 0)
        {
          Breath_Duty--;
        }
        else
        {
          if (Breath_Num && Breath_Num < 100)
            {Breath_Num--;}
          if (Breath_Num)
          {
            Breath_LM = 0;
          }
          else
          {
            Breath_En = 0;
          }
        }
      }
    }
    if (Breath_Cycle < Breath_Duty)
    {
      Choose_Led();
    }
    else
    {
      Close_Led_All();
    }
    //Dispinfo.
  }
}

void Set_Disp_Num(u8 num, u16 low, u16 high, u32 data1, u32 data2)
{
  // LL_GPIO_ResetOutputPin(LED_PWR_EN_PORT,LED_PWR_EN_PIN);
  // 开充电电流
  CHRG_ENABLE;
  Get_Bat_Leve_Map();
  OutInfo.Out_Mos_Interrup_Ctr_Flag = 0;
  OutInfo.Out_Mos_Interrup_Ctr_Flag1 = 0;
  CLR_OUTSTART;
  CLR_OUTLOAD;
  MOS_OFF;
  MOS1_OFF;
  Breath_En = 0;	
  Breath_Count = 0;	
  Breath_Duty = 0;
  Breath_Cycle = 0;
  Dispinfo.Disp_Time = 0;
  Dispinfo.Disp_Num = num;
  Dispinfo.Disp_Low_Time = low;
  Dispinfo.Disp_High_Time = high;
  Dispinfo.Disp_Data = data1;
  Dispinfo.Disp_Data1 = data2;

  ClrShortData();
}

void DISP_Deal(void) // 所有显示相关都写在此函数
{
  if (Dispinfo.Disp_Num)
  {
    if (++Dispinfo.Disp_Time < Dispinfo.Disp_Low_Time)
    {
      Dispinfo.Disp_EN = 0;
    }
    else if (Dispinfo.Disp_Time > Dispinfo.Disp_High_Time) // 一个显示事件结束之后执行
    {

      Dispinfo.Disp_Time = 0;
      if (Dispinfo.Disp_Num < 100)
      {
        Dispinfo.Disp_Num--;
      }

      if (!Dispinfo.Disp_Num)
      {

        if (Dispinfo.Disp_Task == PowerOnReset)
        {
          SysInfo.Sleep_Time = 5;
          Dispinfo.Disp_Task = Idle;
        }
        else
        {
          Dispinfo.Disp_Task = Idle;
        }
        Dispinfo.Disp_Smok_Error_Flag = 0;

        Dispinfo.Disp_EN = 0;
      }
    }
    else
    {
      Dispinfo.Disp_EN = 1;
    }
  }

  else if (OUTLOAD)
  {
  }
  else if (USBIN)
  {
    if (!BatInfo.Ovp_En)
    {
      if (BatInfo.Usb_Ad_Volt >= 1150)
      {
        if (CHRG_IO)
        {
          if (++BatInfo.OvpOn_Cnt >= 50)
          {
            BatInfo.OvpOn_Cnt = 0;
            BatInfo.Ovp_En = 1;
            Disp_Ovp_EN;
          }
          return;
        }
      }
    }
    else
    {
      if (BatInfo.Usb_Ad_Volt <= 1000)
      {
        if (!CHRG_IO)
        {
          if (++BatInfo.OvpOff_Cnt >= 50)
          {
            BatInfo.OvpOff_Cnt = 0;
            BatInfo.Ovp_En = 0;
          }
        }
        Dispinfo.Disp_EN = 0;
      }
      return;
    }

    // 充满后插入USB,立即显示充满
    if (BatInfo.Usb_In_Flag)
    {
      BatVoltage();
      // 插入USB,检测是否给出充满信号或电压高于4.16V
      if (BatInfo.Bat_Volt >= 4160 || CHRG_IO)
      {
        if (++BatInfo.Usb_Full_Cnt >= 20) // 200ms
        {
          BatInfo.Usb_In_Flag = 0;
          Bat_Leve = 5;
          BatInfo.Usb_Full_Flag = 1;
          BatInfo.Usb_Disp_Long_Cnt = 6000; // 充满后60s所有灯熄灭
        }
      }
      else
      {
        BatInfo.Usb_Full_Cnt = 0;
      }
    }

    // 再次发送关RGB LED标志
    if (Dispinfo.Disp_Usb_Ic_Rgb_Off_Flag)
    {
      Dispinfo.Disp_Usb_Ic_Rgb_Off_Flag = 0;
    }

    Get_Bat_Leve_Map();
    Get_Oil_Leve_Map();
    if (!BatInfo.Usb_Full_Flag)
    {
      if (BatInfo.Usb_Led_Twinkle_Cnt < 100)
      {
        BatInfo.Usb_Led_Twinkle_Cnt++;
      }
      else
      {
        BatInfo.Usb_Led_Twinkle_Cnt = 0;
      }

      //				 Dispinfo.Disp_Data = 0;
      Dispinfo.Disp_Data = (BatInfo.Bat_Leve_Data & (~BAT_DISP_MASK)) | OutInfo.Oil_Data_Map;

      if (BatInfo.Usb_Led_Twinkle_Cnt < 50)
      {
        Dispinfo.Disp_Data |= BAT_DISP_MASK;
      }

      Dispinfo.Disp_EN = 1;

      BatVoltage();
      if (BatInfo.Bat_Volt >= 4190 || CHRG_IO)
      {
        if (++BatInfo.Usb_Full_Cnt >= 300) // 3s
        {
          Bat_Leve = 5;
          BatInfo.Usb_Full_Flag = 1;
          BatInfo.Usb_Disp_Long_Cnt = 6000; // 充满后60s所有灯熄灭
        }
      }
    }
    else
    {
      BatInfo.Usb_Full_Cnt = 0;
      // Dispinfo.Disp_Data = 0;
      if (BatInfo.Usb_Disp_Long_Cnt)
      {
        BatInfo.Usb_Disp_Long_Cnt--;
        Dispinfo.Disp_Data = BatInfo.Bat_Leve_Data | BAT_DISP_MASK | OutInfo.Oil_Data_Map;
        Dispinfo.Disp_EN = 1;
      }
      else
      {
        Dispinfo.Disp_EN = 0;
      }
    }
  }
}
