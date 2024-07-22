#include "main.h"

const u16 _Bat_Leve_digit_List[] =
{
        3400,
        3657,
        3699,
        3728,
        3756,
        3787,
        3833,
        3889,
        3945,
        4040,
        4120,
};

const u16 _Bat_Charge_Leve_digit_List[] =
    {
        3610,
        3820,
        3880,
        3920,
        4030,
};

const u32 Oil_Leve_List[] =
    {
        0X20,
        0X21,
        0X23,
        0X27,
        0X2F,
        0X3F,
};

const u32 Bat_Leve_List[] =
    {
        0X800,
        0X840,
        0X8C0,
        0X9C0,
        0XBC0,
        0XFC0,

};

BatInfoTypedef BatInfo;

void BatVoltage(void)
{

  BatInfo.adc_value = GetADCValue(BAT_CHANNEL); // sample vfent
  BatInfo.test_value_1v2 = Adc_CalBatRef();

  BatInfo.Bat_Volt = (u32)BatInfo.test_value_1v2 * 4095ul / BatInfo.adc_value;
}

void Get_Bat_Leve_Map(void)
{
  if (Bat_Leve >= 10)
  {
    // Disp_Bat_Data = c_led_display_100_mask;满电
  }
  else if (Bat_Leve < 10)
  {
    if (Bat_Leve < 1)
    {
      // Disp_Bat_Data = _t_list_digit_list_d0[Bat_Leve];
    }
    else
    {
      // Disp_Bat_Data = _t_list_digit_list_d0[(u8)Bat_Leve%10]|_t_list_digit_list_d1[(u8)Bat_Leve/10];
    }
  }

  // Disp_Bat_Data |= c_led_display_PER_CET_mask;
}

void Get_Power_Rest_BatLeve(void)
{
  u8 i = 0;

  BatVoltage();
  BatInfo.Bat_Low_Lock = 0;

  if (BatInfo.Bat_Volt > _Bat_Leve_digit_List[9])
  {
    Bat_Leve = 10;
  }
  else if (BatInfo.Bat_Volt <= _Bat_Leve_digit_List[0])
  {
    Bat_Leve = 0;
    BatInfo.Bat_Low_Lock = 1;
  }
  else
  {

    for (i = 1; i <= 9; i++)
    {
      if (BatInfo.Bat_Volt <= _Bat_Leve_digit_List[i])
      {

        Bat_Leve = i;
        break;
      }
    }
  }

  Get_Bat_Leve_Map();
}

void Smok_Start_Bat_Leve_Deal(void)
{
  u8 chrgOutVolSub = 0;

  if (!BatInfo.Bat_Leve_Delay_Cnt) // 回复一下电量  最小时间为2.5S
  {
    if (Bat_Leve >= 1)
    {

      // 充电中抽吸，需要减去充电导致的电压浮高，否则将导致充电与未充电掉电电压点不一致
      //  if(USBIN)
      //  {
      // 		chrgOutVolSub = 70;
      //  }else
      //  {
      // 		chrgOutVolSub = 0;
      //  }

      //			 if(BatInfo.Bat_Volt <= _Bat_Leve_digit_List[BatInfo.Bat_Leve-1])//下降太严重了
      //			 {
      //			   Get_Power_Rest_BatLeve();

      //			 }
      //	     else
      if (BatInfo.Bat_Volt <= (_Bat_Leve_digit_List[Bat_Leve - 1]))
      {
        Bat_Leve--;
      }
    }
    else
    {
      BatInfo.Bat_Low_Lock = 1;
      Bat_Leve = 0;
    }
  }

  Get_Bat_Leve_Map();
}
u16 SmokeCnt;
void Get_Bat_Leve(void)
{
  if (OUTLOAD)
  {
    BatInfo.Bat_Leve_Delay_Cnt = 25;
    if ()

      return;
  }

  if (BatInfo.Bat_Leve_Delay_Cnt)
  {
    BatInfo.Bat_Leve_Delay_Cnt--;
  }
  else
  {

    BatVoltage();

    if (USBIN)
    {

      if (Bat_Leve <= 9)
      {

        if (BatInfo.Bat_Volt >= _Bat_Charge_Leve_digit_List[Bat_Leve]) // 大于
        {
          // 5s
          if (++BatInfo.Bat_Charge_Up_Cnt >= 50)
          {
            BatInfo.Bat_Charge_Up_Cnt = 0;
            Bat_Leve++;
            BatInfo.Bat_Low_Lock = 0;
            BatInfo.Bat_Charge_Error_Up_Cnt = 0;
          }
        }
      }
      //				else
      //				{
      //					if(Bat_Leve > 4)
      //					{
      //						 if(++BatInfo.Bat_Charge_Error_Up_Cnt >= 12000)//20分钟强制加一格
      //						 {
      //								BatInfo.Bat_Charge_Error_Up_Cnt = 0;
      //								Bat_Leve += 1;

      //						 }
      //					}
      //				}

      if (Bat_Leve >= 10)
      {
        Bat_Leve = 10;
      }
    }
    else
    {
      BatInfo.Bat_Charge_Up_Cnt = 0;
      BatInfo.Bat_Charge_Error_Up_Cnt = 0;
    }
  }
}
