#ifndef _OUT_H
#define _OUT_H




#define      DUTY_MAX_VOLT              200
#define      DUTY_MIN_VOLT              50

#define 		SMOKE_TIME_OUT 100 // 8s超时

#define     OUT_RMS_EN                  1

#define 		SET_USB_OUT_VOL 		3330
#define 		SET_OUT_VOL 				3530

#define			BAT_START_OUT_LOW_VOL 				3500
#define			BAT_OUT_LOW_VOL 							2950

typedef  struct
{
  u8   Out_Mos_Interrup_Ctr_Flag;
  u8   Out_Mos_Interrup_Ctr_Flag1;
  u8   Out_Mos_Ch_Change_Flag;
	u8   Out_Enable_Flag;
	//u8   Out_Usb_In_Out_Smoke_Cnt;
	u16  Out_Pwm_Duty_Temp;
	u8   Out_Pwm_Duty;
	u8   Out_Pwm_Duty1;
	u8   Out_Pwm_Cycle;
	u8   Out_Pwm_Cycle1;
	u8   Out_Duty_Main_Deal_Flag;
	u8   Out_Duty_Main_Deal_Flag1;
	u8   Out_Short_Check_En_Flag;
	u8   Out_Short_Check_En_Flag1;
  u8   Bat_Low_Cnt;
	u16  Out_Adc_Volt;
	u16  Out_Volt;
	u16  Out_Volt1;
  u16  Short_Volt;
	u8   Smok_Time;
	u16  Set_Out_Volt;
//  u8   Oil_Leve;
	u8   Out_Gear_Leve;
  u8   Out_Gear_Leve_Last;
//	u32  Out_Oil_Time;
	u32  Oil_Data_Map;
	u8   Out_High_Res_Cnt;
	
}OutInfoTypedef;

extern __IO u32 Out_Oil_Time		__attribute__((at(0x20000A00)));		//油量计数器
extern __IO u8 Oil_Leve __attribute__((at(0x20000A20)));		//油量
extern __IO u32 Short_Reset_Flag __attribute__((at(0x20000A30)));		//复位标志
extern __IO u32 Short_Reset_Flag1 __attribute__((at(0x20000A40)));		//复位标志

extern  OutInfoTypedef    OutInfo;
extern  void    Get_Oil_Leve(void);
extern  void    Get_Oil_Leve_Map(void);
extern  void    Out_Deal(void);
extern  void    Interrup_Ctr_Mos_Deal(void);

extern  void 		SetShortData(void);
extern  void 		ClrShortData(void);
extern  u8 			ShortIsData(void);

#endif


