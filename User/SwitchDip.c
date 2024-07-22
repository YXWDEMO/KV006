#define __SWITCH_DIP_C__
#include "main.h"

u8	keyChangCnt=0;
u8	keyHoldCnt=0;		//�˲�����
u16	keyReleaseCnt=0;		//�����ͷ�ʱ��
u8	last_mode=10;
u16  keyval=0;

static u16    Get_Switch_Ad(void)
{
	u16  switchAdcValue = 0;

  switchAdcValue = GetADCValue(SWITCH_CHANNEL);

	return switchAdcValue;
}

void 	Switch_Init(void)
{
   keyval = Get_Switch_Ad();

  if(keyval>=3300)
	{
		swInfo.swGeras = SW_GERAS_L2;
		SysInfo.systemState = SYSTEM_DILE;
	}
	else if(keyval<=100)
	{
		swInfo.swGeras = SW_GERAS_L1;
		SysInfo.systemState = SYSTEM_DILE;
	}
	else if(keyval>=1000 && keyval<=3000)
	{
		swInfo.swGeras = SW_GERAS_L0;
		SysInfo.systemState = SYSTEM_OFF;
	}

	swInfo.swGerasOld=swInfo.swGeras;
}

void Switch_Scan(void)
{

	if(OUTLOAD)
	{
		keyHoldCnt = 0;
		keyReleaseCnt = 0;
		keyChangCnt = 0;
		swInfo.swGerasOld=swInfo.swGeras;
		return;
	}

//	if(keyReleaseCnt)
//	{
//			keyReleaseCnt--;
//			if(keyReleaseCnt == 0)
//			{
//				if(swInfo.swGeras == SW_GERAS_L0)
//				{
//					SysInfo.systemState = SYSTEM_OFF;
//					if(Dispinfo.Dis_Change_Gears_Effect == CHANGE_GEARS_EFFECT_L1)
//					{
//						// ��ʾL1��L0�ʵ�Ч��
//						Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L1_L0;
//					}else if(Dispinfo.Dis_Change_Gears_Effect == CHANGE_GEARS_EFFECT_L2)
//					{
//						// ��ʾL2��L0�ʵ�Ч��
//						Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L2_L0;
//					}
//				}else if(swInfo.swGeras == SW_GERAS_L1)
//				{
//					SysInfo.systemState = SYSTEM_DILE;
//					// ��ʾL1�ʵ�Ч��
//					Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L1;
//				}else if(swInfo.swGeras == SW_GERAS_L2)
//				{
//					SysInfo.systemState = SYSTEM_DILE;
//					// ��ʾL2�ʵ�Ч��
//					Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L2;
//				}

//				// ��ʾ����
//				Disp_Gear;
//			}
//	}

	if(++keyHoldCnt >= 10)
	{
		keyHoldCnt=0;
		keyval = Get_Switch_Ad();

		if(keyval>=3300)
		{
			swInfo.swGeras = SW_GERAS_L2;
		}
		else if(keyval<=100)
		{
			swInfo.swGeras = SW_GERAS_L1;
		}
		else if(keyval>=1000 && keyval<=3000)
		{
			swInfo.swGeras = SW_GERAS_L0;
		}

		if (swInfo.swGeras!=swInfo.swGerasOld)
		{
			keyChangCnt++;
			if(keyChangCnt >= 3)
			{
				if(swInfo.swGeras == SW_GERAS_L0)
				{
					SysInfo.systemState = SYSTEM_OFF;
					if(Dispinfo.Dis_Change_Gears_Effect == CHANGE_GEARS_EFFECT_L1)
					{
						// ��ʾL1��L0�ʵ�Ч��
						Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L1_L0;
					}else if(Dispinfo.Dis_Change_Gears_Effect == CHANGE_GEARS_EFFECT_L2)
					{
						// ��ʾL2��L0�ʵ�Ч��
						Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L2_L0;
					}
				}else if(swInfo.swGeras == SW_GERAS_L1)
				{
					SysInfo.systemState = SYSTEM_DILE;
					// ��ʾL1�ʵ�Ч��
					Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L1;
				}else if(swInfo.swGeras == SW_GERAS_L2)
				{
					SysInfo.systemState = SYSTEM_DILE;
					// ��ʾL2�ʵ�Ч��
					Dispinfo.Dis_Change_Gears_Effect = CHANGE_GEARS_EFFECT_L2;
				}

				// ��ʾ����
				Disp_Gear;

				swInfo.swGerasOld=swInfo.swGeras;
			}
		}else
		{
			keyChangCnt = 0;
		}
	}

}	

