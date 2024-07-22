#ifndef _SYS_H
#define _SYS_H

typedef enum{
	SYSTEM_DILE, // ����
	SYSTEM_OFF,	 // �ػ�
}SystemState_t;

typedef   struct
{
  u8   Sleep_Time;
  u8   Time_1ms;
	u8   Time_10ms;
	u8   Time_100ms;

	u8   _1ms_Flag;
	u8   _10ms_Flag;
	u8   _100ms_Flag;

  u8   Power_Rest;
  SystemState_t   systemState;

}SysInfoTypedef;




extern SysInfoTypedef  SysInfo;










extern void Sys_Init(void);





#endif


