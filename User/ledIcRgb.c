#include "main.h"

#if 0
u8 run_led_bit;
u8 run_led_15ms;

//@@闪烁
u8	ledOnTime=0;
u8	ledOnTimeCnt=0;
u8	ledOffTime=0;
u8	ledOffTimeCnt=0;
u8	ledDispDelCnt=0;
u8	ledFlaCnt=0;
//@@闪烁和呼吸公用
u64 ledDispBitMap=0;
//@@呼吸
u8	ledBreDuty=0;
//u8	ledBreCnt=0;
u8	ledBreUpStepLenSet=0;
u8	ledBreDownStepLenSet=0;
u8	ledFlaBreFlag=false;
//u8	ledBreDir=false;
u8	breFreDivCnt=0;

/// LED RGB IC运行参数
// 当前正在向那个IC灯发送数据
volatile u8 	ledIcWrtieCurrentCnt = 0;

// 写使能标志
volatile  u8 ledIcWrtieEn = 0;
// 运行状态
LEDIcRunDir_t LEDIcRunDir = Water_Lamps_Dir_None;
u8 UpdateLEDIcNum = 0;
u8 *CurrentDispColorTab = NULL;

u8	LEDBuff[3]={0};
u8	led_COUNT[IC_RGB_BUFF_SIZE];
u8	stLEDBright[IC_RGB_BUFF_SIZE];
u8	ledBreDir[IC_RGB_BUFF_SIZE];

u8	ledBreCnt[IC_RGB_BUFF_SIZE];

u8 BreDuty[IC_RGB_BUFF_SIZE];

u8 flash_led_data=0;        //发送数据标志位，避免重复发送浪费CPU资源
u8 led_key_flag=0;
u8 led_flag=0;

//const u8 color_Steps_Tab[] = 
//{
//    0x00,0x00,0x00,0x00,0x00,
//	  0x00,0x00,0x00,0x00,0x00,
//	  0x00,0x00,0x00,0x00,0x00,
//	  0x00,0x00,0x00,0x00,0x00,
//	  0x00,0x00,0x00,0x00,0x00,
//	  0x15,0x2A,0x3F,0x55,0x6A,
//	  0x7F,0x94,0xAA,0xBF,0xD4,0xE9,
//	  0xFF,0xFF,0xFF,0xFF,0xFF,
//	  0xFF,0xFF,0xFF,0xFF,0xFF,
//	  0xFF,0xFF,0xFF,0xFF,0xFF,
//	  0xFF,0xFF,0xFF,0xFF,0xFF,
//	  0xFF,0xFF,0xFF,0xFF,0xFF,
//};


u8 Smoke_Dis_Color_Tab[66] = {0x00};


const u8 L1_LOGO_Color_Tab[] = 
{
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
	
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
	
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
};

const u8 L2_LOGO_Color_Tab[] = 
{
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
	
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
	
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,

    0xFF,0x17,0x00,0xFF,0x17,0x00,
		0xFF,0x17,0x00,0xFF,0x17,0x00,
		0xFF,0x17,0x00,0xFF,0x17,0x00,
};

const u8 Clr_Color_Tab[] = 
{
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
	
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
	
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,

};

const u8 Watt_Gears_L1_Color_Tab[] = 
{
    0x00,0x00,0xFF,0x00,0x00,0xFF,
		0x00,0x00,0xFF,0x00,0x00,0xFF,
		0x00,0x00,0xFF,0x00,0x00,0xFF,
		0x00,0x00,0xFF,0x00,0x00,0xFF,

		0x00,0xFF,0xFF,0x00,0xFF,0xFF,
		0x00,0xFF,0xFF,0x00,0xFF,0xFF,
		0x00,0xFF,0xFF,0x00,0xFF,0xFF,

		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,

};

const u8 Watt_Gears_L2_Color_Tab[] = 
{
    0xFF,0x17,0x00,0xFF,0x17,0x00,
		0xFF,0x17,0x00,0xFF,0x17,0x00,
		0xFF,0x17,0x00,0xFF,0x17,0x00,
		0xFF,0x17,0x00,0xFF,0x17,0x00,
	
		0xFF,0xFF,0x00,0xFF,0xFF,0x00,
		0xFF,0xFF,0x00,0xFF,0xFF,0x00,
		0xFF,0xFF,0x00,0xFF,0xFF,0x00,
	
		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
		0x00,0xFF,0x00,0x00,0xFF,0x00,
};

const u8 Err_Color_Tab[] = {
    0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		
    0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		
    0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,
		0xFF,0x00,0x00,0xFF,0x00,0x00,

};


// 获取对应功率档位的LOGO颜色表
u8* GetWattLogoColorTab(u8 wattLevel)
{
	if(wattLevel == SW_GERAS_L1)
	{
		return (u8*)L1_LOGO_Color_Tab;
	}else if(wattLevel == SW_GERAS_L2)
	{
		return (u8*)L2_LOGO_Color_Tab;
	}

	return (u8*)L1_LOGO_Color_Tab;
}


// 获取对应功率档位的颜色表
u8* GetWattGearsColorTab(u8 wattLevel)
{
	if(wattLevel == SW_GERAS_L1)
	{
		return (u8*)Watt_Gears_L1_Color_Tab;
	}else if(wattLevel == SW_GERAS_L2)
	{
		return (u8*)Watt_Gears_L2_Color_Tab;
	}

	return (u8*)Watt_Gears_L1_Color_Tab;
}

/*=================================================1615RGB 幻彩发光二极管===========================================================*/

void led_rgb_driver(u8 R, u8 G, u8 B)
{
	//u32 rgb_bit;// = (u32)W|((u32)B<<8)|((u32)R<<16)|((u32)G<<24); //样品的rgb顺序是 GRB  
	LEDBuff[0]=B;
	LEDBuff[1]=R;
	LEDBuff[2]=G;

    //G
    if(LED_BUFF_BIT23) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT22) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT21) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT20) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT19) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT18) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT17) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT16) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    //R
    if(LED_BUFF_BIT15) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT14) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT13) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT12) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT11) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT10) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT9) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT8) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    //B
    if(LED_BUFF_BIT7) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT6) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT5) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT4) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT3) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT2) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT1) 	LED_SEND_BIT1() else LED_SEND_BIT0()
    if(LED_BUFF_BIT0) 	LED_SEND_BIT1() else LED_SEND_BIT0()

}

void key_rgb_driver(u8 R, u8 G, u8 B)
{
	//u32 rgb_bit;// = (u32)W|((u32)B<<8)|((u32)R<<16)|((u32)G<<24); //样品的rgb顺序是 GRB  
	LEDBuff[0]=B;
	LEDBuff[1]=R;
	LEDBuff[2]=G;

    //G
    if(LED_BUFF_BIT23) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT22) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT21) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT20) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT19) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT18) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT17) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT16) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    //R
    if(LED_BUFF_BIT15) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT14) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT13) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT12) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT11) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT10) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT9) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT8) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    //B
    if(LED_BUFF_BIT7) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT6) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT5) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT4) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT3) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT2) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT1) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
    if(LED_BUFF_BIT0) 	LED_SEND2_BIT1() else LED_SEND2_BIT0()
}


/*
** @berf: 更新指定灯的颜色(仅更新缓存)
** @param updateIndex:灯的索引即更新第几个灯(注意索引从0开始)
** @param color 更新的颜色
** @return: null
*/
static void UpdateLedIcDiaplayData(u8 updateIndex,u8 *color)
{
	if(updateIndex >= IC_RGB_NUM)
	{
		return;
	}

	u8 updateLedIcIndex =  updateIndex*3;

	stLEDBright[updateLedIcIndex]	 = color[0];
	stLEDBright[updateLedIcIndex+1] = color[1];
	stLEDBright[updateLedIcIndex+2] = color[2];
}


/*
** @berf: 设置运行时间
** @param UpdateLEDStartIndex LED开始的索引
** @param UpdateLEDNum 本次更新多少个灯
** @param DisColorTab 显示的颜色表
** @param DisColorTabSize 显示颜色表的大小
** @param UpdateDisFlag 更新显示标志 1开始更新 0不更新
** @param resetFlag 复位标志 1需要复位 0不需要 (即需不需要从头开始更新)
*/
void SetLEDIcRunParam(u8 UpdateLEDStartIndex, u8 UpdateLEDNum, u8 DisLEDNum,u8* DisColorTab, u8 DisColorTabSize, u8 UpdateDisFlag,u8 resetFlag)
{

	if((DisColorTab == NULL) || ((UpdateLEDNum*3) > DisColorTabSize))
	{
		return;
	}

	ledIcWrtieEn = 0;
	UpdateLEDIcNum = DisLEDNum*3;

	CurrentDispColorTab = DisColorTab;

	for(u8 i = UpdateLEDStartIndex; i < (UpdateLEDStartIndex+UpdateLEDNum); i++)
	{
		UpdateLedIcDiaplayData(i,CurrentDispColorTab+(i*3));
	}

//	if(resetFlag)
//	{
//		LED_SEND_RESET();
//	}

	if(UpdateDisFlag)
	{
		ledIcWrtieCurrentCnt = 0;
		ledIcWrtieEn = 1;
	}

}


void SetUpdateLEDIcNum(u8 DisLEDNum)
{
	if(DisLEDNum > IC_RGB_NUM)
	{
		return;
	}

	UpdateLEDIcNum = DisLEDNum*3;
	ledIcWrtieCurrentCnt = 0;
	ledIcWrtieEn = 1;
}


/*
** @berf: 实际更新灯颜色（即颜色同步到LED上）
** @param null
** @return: null
*/
void LED_Ic_Handle(void)
{
		if(ledIcWrtieEn == 0 || ledIcWrtieCurrentCnt > UpdateLEDIcNum  || ledIcWrtieCurrentCnt > IC_RGB_BUFF_SIZE)
		{
			return;
		}

		// 一次发1个灯的数据，以给其他任务留出执行时间
		led_rgb_driver(stLEDBright[ledIcWrtieCurrentCnt], stLEDBright[ledIcWrtieCurrentCnt+1], stLEDBright[ledIcWrtieCurrentCnt+2]);
		ledIcWrtieCurrentCnt+=3;
}


void LED_SetPwm(u8 led, u8 brightness)
{
	/*
	if(led%3==1)	//green 亮度降低
		stLEDBright[led]=brightness/3;
	else	
		stLEDBright[led]=brightness/2;
	*/
	stLEDBright[led]=brightness;
}

void set_led_hx(void)
{
    led_COUNT[2]=16; led_COUNT[1]=56; led_COUNT[0]=32;
    led_COUNT[5]=21; led_COUNT[4]=51; led_COUNT[3]=27;
    led_COUNT[8]=31; led_COUNT[7]=41; led_COUNT[6]=17;
    led_COUNT[11]=60;led_COUNT[10]=36;led_COUNT[9]=12;
    led_COUNT[14]=55;led_COUNT[13]=31;led_COUNT[12]=17;

    led_COUNT[17]=33;led_COUNT[16]=43;led_COUNT[15]=18;
    led_COUNT[20]=30;led_COUNT[19]=46;led_COUNT[18]=21;
    led_COUNT[23]=27;led_COUNT[22]=49;led_COUNT[21]=24;
    led_COUNT[26]=24;led_COUNT[25]=51;led_COUNT[24]=27;
    led_COUNT[29]=45;led_COUNT[28]=31;led_COUNT[27]=6;
    led_COUNT[32]=45;led_COUNT[31]=31;led_COUNT[30]=6;
    led_COUNT[35]=45;led_COUNT[34]=31;led_COUNT[33]=6;
    led_COUNT[38]=45;led_COUNT[37]=31;led_COUNT[36]=6;
    led_COUNT[41]=45;led_COUNT[40]=31;led_COUNT[39]=6;
    led_COUNT[44]=45;led_COUNT[43]=31;led_COUNT[42]=6;
    led_COUNT[47]=45;led_COUNT[46]=31;led_COUNT[45]=6;
    led_COUNT[50]=45;led_COUNT[49]=31;led_COUNT[48]=6;
    led_COUNT[53]=45;led_COUNT[52]=31;led_COUNT[51]=6;
    led_COUNT[56]=45;led_COUNT[55]=31;led_COUNT[54]=6;
    led_COUNT[59]=45;led_COUNT[58]=31;led_COUNT[57]=6;
    led_COUNT[62]=45;led_COUNT[61]=31;led_COUNT[60]=6;
    led_COUNT[65]=45;led_COUNT[64]=31;led_COUNT[63]=6;
    led_COUNT[68]=45;led_COUNT[67]=31;led_COUNT[66]=6;
    led_COUNT[71]=45;led_COUNT[70]=31;led_COUNT[69]=6;
    led_COUNT[74]=45;led_COUNT[73]=31;led_COUNT[72]=6;
    led_COUNT[77]=45;led_COUNT[76]=31;led_COUNT[75]=6;
    led_COUNT[80]=45;led_COUNT[79]=31;led_COUNT[78]=6;
    led_COUNT[83]=45;led_COUNT[82]=31;led_COUNT[81]=6;

    ledBreDir[0]=1; ledBreDir[1]=1; ledBreDir[2]=1;
    ledBreDir[3]=1; ledBreDir[4]=1; ledBreDir[5]=1;
    ledBreDir[6]=0; ledBreDir[7]=1; ledBreDir[8]=1;
    ledBreDir[9]=1; ledBreDir[10]=1;ledBreDir[11]=1;
    ledBreDir[12]=1;ledBreDir[13]=1;ledBreDir[14]=1;


    ledBreDir[15]=1;ledBreDir[16]=1;ledBreDir[17]=0;
    ledBreDir[18]=1;ledBreDir[19]=1;ledBreDir[20]=0;
    ledBreDir[21]=1;ledBreDir[22]=1;ledBreDir[23]=0;
    ledBreDir[24]=1;ledBreDir[25]=1;ledBreDir[26]=0;
    ledBreDir[27]=1;ledBreDir[28]=1;ledBreDir[29]=0;
    ledBreDir[30]=1;ledBreDir[31]=1;ledBreDir[32]=0;
    ledBreDir[33]=1;ledBreDir[34]=1;ledBreDir[35]=0;
    ledBreDir[36]=1;ledBreDir[37]=1;ledBreDir[38]=0;
    ledBreDir[39]=1;ledBreDir[40]=1;ledBreDir[41]=0;
    ledBreDir[42]=1;ledBreDir[43]=1;ledBreDir[44]=0;
    ledBreDir[45]=1;ledBreDir[46]=1;ledBreDir[47]=0;
    ledBreDir[48]=1;ledBreDir[49]=1;ledBreDir[50]=0;
    ledBreDir[51]=1;ledBreDir[52]=1;ledBreDir[53]=0;
    ledBreDir[54]=1;ledBreDir[55]=1;ledBreDir[56]=0;
    ledBreDir[57]=1;ledBreDir[58]=1;ledBreDir[59]=0;
    ledBreDir[60]=1;ledBreDir[61]=1;ledBreDir[62]=0;
    ledBreDir[63]=1;ledBreDir[64]=1;ledBreDir[65]=0;
    ledBreDir[66]=1;ledBreDir[67]=1;ledBreDir[68]=0;
    ledBreDir[69]=1;ledBreDir[70]=1;ledBreDir[71]=0;
    ledBreDir[72]=1;ledBreDir[73]=1;ledBreDir[74]=0;
    ledBreDir[75]=1;ledBreDir[76]=1;ledBreDir[77]=0;
    ledBreDir[78]=1;ledBreDir[79]=1;ledBreDir[80]=0;
    ledBreDir[81]=1;ledBreDir[82]=1;ledBreDir[83]=0;
		
}

/*
**	@bref:设置呼吸数据
**	@param:null
**	@ret: null
*/
#if 0
void set_bre_data(void)
{
	static u8 i=0;

	for(i=0;i<IC_RGB_BUFF_SIZE;i++)
	{
		if(ledBreDir[i]==1)
		{
				//if(led_COUNT[i]<51)
				if(led_COUNT[i]<60)
				{
						led_COUNT[i]++;
						stLEDBright[i]=color_Steps_Tab[led_COUNT[i]];
		
				}
				else
				{
						ledBreDir[i]=0;
						led_COUNT[i]=35;
						stLEDBright[i]=color_Steps_Tab[led_COUNT[i]];

				}
		}
		else
		{
				//if(led_COUNT[i]>25)
				if(led_COUNT[i]>0)
				{
						led_COUNT[i]--;
						stLEDBright[i]=color_Steps_Tab[led_COUNT[i]];
		
				}
				else
				{
						ledBreDir[i]=1;
						led_COUNT[i]=25;	 
						stLEDBright[i]=color_Steps_Tab[led_COUNT[i]];
					
				}
		}
	}

//    LL_TIM_DisableIT_UPDATE(TIM14);
//    LL_TIM_DisableIT_UPDATE(TIM1);

//    led_rgb_driver(stLEDBright[0], stLEDBright[1], stLEDBright[2]);	
//    led_rgb_driver(stLEDBright[3], stLEDBright[4], stLEDBright[5]);	
//    led_rgb_driver(stLEDBright[6], stLEDBright[7], stLEDBright[8]);
//    LL_TIM_EnableIT_UPDATE(TIM1);
//    LL_TIM_DisableIT_UPDATE(TIM1);
//    led_rgb_driver(stLEDBright[9], stLEDBright[10], stLEDBright[11]);
//    led_rgb_driver(stLEDBright[12], stLEDBright[13], stLEDBright[14]);
//    LL_TIM_EnableIT_UPDATE(TIM1);
//	  LL_TIM_EnableIT_UPDATE(TIM14);
			UpdateLEDIcNum = IC_RGB_BUFF_SIZE;
			ledIcWrtieCurrentCnt = 0;
			ledIcWrtieEn = 1;
}
#endif

void SetflashLedDataFlag(void)
{
	flash_led_data = 0;
}

/*
*函数名    : LedIcAllOff
*函数功能  : 灯的显示设置函数
*函数参数  : u8 breDutyVal--占空比
*函数返回值: void
*函数描述  : 
*/
void    LedIcAllOff(void)
{
    static u8 i;
    if(flash_led_data==0)
		{
        flash_led_data=1;       //只发一次
				LED_SEND_RESET();
				for(i=0;i<IC_RGB_BUFF_SIZE;i++)
        {
            stLEDBright[i]=0;
        }
				
				UpdateLEDIcNum = IC_RGB_BUFF_SIZE;
				ledIcWrtieCurrentCnt = 0;
				ledIcWrtieEn = 1;
        //LED_Write();
		}
}

// 更新所有将LED IC全部更新为一个颜色
void    LedIcColorUpdateAll(u32 color)
{
    static u8 i;
    if(flash_led_data==0)
		{
        flash_led_data=1;       //只发一次
				LED_SEND_RESET();
				for(i = 0;i < IC_RGB_BUFF_SIZE;i += 3)
        {
            stLEDBright[i] = color>>16;
						stLEDBright[i+1] = (color&0x00ff00)>>8;
						stLEDBright[i+2] = color&0x0000ff;
        }

				UpdateLEDIcNum = IC_RGB_BUFF_SIZE;
				ledIcWrtieCurrentCnt = 0;
				ledIcWrtieEn = 1;
        //LED_Write();
		}
}

/*
*Function    : LedIcAllUpdate
*函数功能  : 灯的显示设置函数
*函数参数  : LEDUpdateStart 开始更新位置
*@param: ColorTab 需要更新的颜色表
*@param: size 更新的大小
*函数返回值: void
*/
void LedIcColorUpdate(u8 LEDUpdateStart, u8 *ColorTab,u8 size,u8 updateLedNum)
{
    static u8 i;
    if(flash_led_data==0)
		{
        flash_led_data=1;       //只发一次
				LED_SEND_RESET();
				for(i = LEDUpdateStart; i < (LEDUpdateStart+size+1); i++)
        {
            stLEDBright[i]=ColorTab[i-LEDUpdateStart];
        }

				UpdateLEDIcNum = updateLedNum;
				ledIcWrtieCurrentCnt = 0;
				ledIcWrtieEn = 1;
        //LED_Write();
		}
}

/*==============================================================================
*函数名    : LedDispSel
*函数功能  : 灯的显示设置函数
*函数参数  : u8 breDutyVal--占空比
*函数返回值: void
*函数描述  : 
==============================================================================*/
void 	LedDispSel(u8 breDutyVal)
{
	static u8 i;

	if(flash_led_data==0)
	{
			flash_led_data=1;       //只发一次

			for(i = 0;i < IC_RGB_BUFF_SIZE;i++) 
			{
					if(ledDispBitMap&((u64)1<<i))
					{
							LED_SetPwm(i,breDutyVal) ;
					}
					else
					{
							stLEDBright[i]=0;
					}
			}

			ledIcWrtieCurrentCnt = 0;
			ledIcWrtieEn = 1;
	    //LED_Write();
    }
}



/*==============================================================================
*函数名    : LedBreDispSel
*函数功能  : 呼吸灯显示设置函数
*函数参数  : void
*函数返回值: void
*函数描述  : 
==============================================================================*/

void 	LedBreDispSel(u8 breDutyVal)
{
	static u8 i;
	if(flash_led_data==0)
	{
			flash_led_data=1;       //只发一次
      
			for(i=0;i<IC_RGB_BUFF_SIZE;i++) 
			{
					if(ledDispBitMap&((u64)1<<i)) 
					{
							LED_SetPwm(i,BreDuty[i]) ;
					}
			}

			ledIcWrtieCurrentCnt = 0;
			ledIcWrtieEn = 1;
			//LED_Write();
    }
}


/* 闪烁/呼吸判断 */
void 	LedHand(void)
{
	if(ledFlaBreFlag == 0)
		LedFlaDeal();       //闪烁函数
	else
		LedBreDeal();       //呼吸函数
}


/************************************************************************
 *函数名:LedFlaSet
 *函数描述:LED闪烁设置
 *输入参数:
 			(1)dispBitMap:bit0:Red	bit1:Green	bit2:Blue
 			(2)onTime:亮的时间:onTime*闪烁执行函数调用周期
 			(3)offTime:灭的时间:offTime*闪烁执行函数调用周期
 			(4)flaCnt:闪烁次数(即亮灭次数)
 			(5)delTimeCnt:闪烁之前灭灯准备时间:delTimeCnt*闪烁执行函数调用周期
 *返回参数:无
 *返回类型:无
 *    注意事项:	(1)亮灯最长设置时间为255*闪烁执行函数调用周期
 				(2)灭灯最长设置时间为255*闪烁执行函数调用周期
 				(3)如果变量dispBitMap==0xff,则dispBitMap保持不变
 				(4)如果flaCnt>=100,则会持续闪烁下去直到强制关闭闪烁
************************************************************************/
void LedFlaSet(u64 dispBitMap,u8 onTime,u8 offTime,u8 flaCnt,u8 delTimeCnt)
{
	   run_led_bit=0;
	   run_led_15ms=0;

    flash_led_data=0;
//    if(dispBitMap!=0xff)
    ledDispBitMap=dispBitMap;   //选择对应的灯
    ledOnTime=onTime;               //亮的时间
    ledOffTime=offTime;             //灭的时间
    ledFlaCnt=flaCnt;               //闪烁次数
    ledDispDelCnt=delTimeCnt;       //闪烁之前灭灯准备时间

    ledOnTimeCnt=0;
    ledOffTimeCnt=0;

    ledFlaBreFlag=false;
    ledBreDuty=0;
}


/*************************************************************
 *函数名:LedFlaHand
 *函数描述:LED 闪烁/长亮/长灭执行函数,放在10ms时基内执行
 *输入参数:无
 *返回参数:无
 *返回类型:无
 *    注意事项:	(1)需要使用ledFlaBreFlag选择执行
 					false:闪烁函数
 					true:呼吸函数
 				(2)此函数的调用周期设定为10ms,这样最长亮灯时间
 				可达到655s,如果需要更长的亮灯可自行添加变量调度
*************************************************************/
void LedFlaDeal(void)
{
    if(ledDispDelCnt)
    {
        ledDispDelCnt--;
        LedIcAllOff();
        return;
    }

    if(ledOnTime==0)
    {
        LedIcAllOff();
    }
    else 	if(ledOnTime>0 && ledOffTime==0)			//长亮
    {
        LedDispSel(LED_BRE_PERI_MAX);
    }
    else 	if(ledFlaCnt)                               //闪烁
    {
        if(ledOnTimeCnt<ledOnTime)
        {
            if (ledOnTimeCnt==0)
            {
                flash_led_data=0;
            }
            ledOnTimeCnt++;
            LedDispSel(LED_BRE_PERI_MAX);
        }
        else 	if(ledOffTimeCnt<ledOffTime)
        {
            if (ledOffTimeCnt==0)
            {
                flash_led_data=0;
            }
            ledOffTimeCnt++;
            if(ledOffTimeCnt==ledOffTime)
            {
                if(ledFlaCnt<100 && ledFlaCnt)
                    ledFlaCnt--;
                ledOnTimeCnt=0;
                ledOffTimeCnt=0;
            }

            LedIcAllOff();
        }
    }
    else
    {
        LedIcAllOff();
        ledOnTimeCnt=0;
        ledOffTimeCnt=0;
    }
}

/*************************************************************
 *函数名:LedBreRea
 *函数描述:LED呼吸准备设置函数
 *输入参数:	dispBitMap:bit0:Red	bit1:Green	bit2:Blue
 			upTime:上升步距设置,上升时间为:upTime*函数调用周期
 			downTime:下降步距设置,下降时间为:downTime*函数调用周期
 			breCnt:呼吸次数设置
 			breDir:呼吸的方向:指定开始呼吸的方向 0:渐亮，1:渐灭
            dutyKeepFlag:是否保持原占空比 0:重新设置，1:保持原占空比
 *返回参数:无
 *返回类型:无
 *    注意事项:	(1)如果dispBitMap==0xff,则ledDispBitMap保持不变
 				(2)upTime和downTime的时基为10ms
 				(3)步距不再进行计算,根据自己的需要计算好传入即可
					,目的是避免除法运算,节省空间
 				(4)如果开始呼吸的方向向下,则设置呼吸次数时需将
 					需要的呼吸次数-1
*************************************************************/
void LedBreRea(u64 dispBitMap,u8 upTime,u8 downTime,u8 breCnt,u8 breDir,u8 i)
{
    flash_led_data=0;
//    if(dispBitMap!=0xff)
        ledDispBitMap=dispBitMap;

    ledBreDir[i]=breDir;       //breDir:呼吸的方向
    if(ledBreDir[i]==false)
        BreDuty[i]=LED_BRE_PERI_MIN;
    else
    {
        BreDuty[i]=LED_BRE_PERI_MAX;
    }
    ledBreCnt[i]=breCnt;                   //breCnt:呼吸次数设置

    //@@上升步距计算
    ledBreUpStepLenSet=upTime;          //渐亮步距
    //@@下降步距计算
    ledBreDownStepLenSet=downTime;      //渐灭步距

    ledFlaBreFlag=true;
}

/**
 *函数名:LedBreDeal
 *函数描述:呼吸执行函数
 *输入参数:无
 *返回参数:无
 *返回类型:无
 *    注意事项:	(1)此函数的执行调用周期为10ms
				(2)如果ledBreCnt>=100,呼吸将会不停执行下去直到
					强制停止
				(3)呼吸至最亮或者呼吸至最暗均为1次,所以呼吸次数
					需要自行计算
**/
void 	LedBreDeal(void)
{
    static u8	i=0;
 
//        for(i=0;i<39;i++)
	  for(i=0;i<IC_RGB_BUFF_SIZE;i++)
    {
        if(!(ledDispBitMap & ((u64)1<<i)))
        {
        //	LedBreDispSel(0);
            continue;
        }
        
        if(ledBreDir[i]==false)
        {
            if(BreDuty[i]<LED_BRE_PERI_MAX-ledBreUpStepLenSet)//ledBreUpStepLenSet上升步距
                BreDuty[i]+=ledBreUpStepLenSet;
            else
            {
                BreDuty[i]=LED_BRE_PERI_MAX;        //ledBreDuty占空比
                if(ledBreCnt[i]<100 && ledBreCnt[i])      //ledBreCnt呼吸次数
                    ledBreCnt[i]--;
                if(ledBreCnt[i])
                    ledBreDir[i]=true;                 //breDir呼吸方向
            }
        }
        else
        {
            //@@原始程序
            if(BreDuty[i]>ledBreDownStepLenSet)     //ledBreDownStepLenSet下降步距
                BreDuty[i]-=ledBreDownStepLenSet;
            else
            {
                BreDuty[i]=0;
                if(ledBreCnt[i]<100 && ledBreCnt[i])
                    ledBreCnt[i]--;
                if(ledBreCnt[i])
                    ledBreDir[i]=false;
            }
        }
    }


    flash_led_data=0;
		LedBreDispSel(BreDuty[i]);     //灯的显示设置函数
}

#endif
