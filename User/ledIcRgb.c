#include "main.h"

#if 0
u8 run_led_bit;
u8 run_led_15ms;

//@@��˸
u8	ledOnTime=0;
u8	ledOnTimeCnt=0;
u8	ledOffTime=0;
u8	ledOffTimeCnt=0;
u8	ledDispDelCnt=0;
u8	ledFlaCnt=0;
//@@��˸�ͺ�������
u64 ledDispBitMap=0;
//@@����
u8	ledBreDuty=0;
//u8	ledBreCnt=0;
u8	ledBreUpStepLenSet=0;
u8	ledBreDownStepLenSet=0;
u8	ledFlaBreFlag=false;
//u8	ledBreDir=false;
u8	breFreDivCnt=0;

/// LED RGB IC���в���
// ��ǰ�������Ǹ�IC�Ʒ�������
volatile u8 	ledIcWrtieCurrentCnt = 0;

// дʹ�ܱ�־
volatile  u8 ledIcWrtieEn = 0;
// ����״̬
LEDIcRunDir_t LEDIcRunDir = Water_Lamps_Dir_None;
u8 UpdateLEDIcNum = 0;
u8 *CurrentDispColorTab = NULL;

u8	LEDBuff[3]={0};
u8	led_COUNT[IC_RGB_BUFF_SIZE];
u8	stLEDBright[IC_RGB_BUFF_SIZE];
u8	ledBreDir[IC_RGB_BUFF_SIZE];

u8	ledBreCnt[IC_RGB_BUFF_SIZE];

u8 BreDuty[IC_RGB_BUFF_SIZE];

u8 flash_led_data=0;        //�������ݱ�־λ�������ظ������˷�CPU��Դ
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


// ��ȡ��Ӧ���ʵ�λ��LOGO��ɫ��
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


// ��ȡ��Ӧ���ʵ�λ����ɫ��
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

/*=================================================1615RGB �òʷ��������===========================================================*/

void led_rgb_driver(u8 R, u8 G, u8 B)
{
	//u32 rgb_bit;// = (u32)W|((u32)B<<8)|((u32)R<<16)|((u32)G<<24); //��Ʒ��rgb˳���� GRB  
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
	//u32 rgb_bit;// = (u32)W|((u32)B<<8)|((u32)R<<16)|((u32)G<<24); //��Ʒ��rgb˳���� GRB  
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
** @berf: ����ָ���Ƶ���ɫ(�����»���)
** @param updateIndex:�Ƶ����������µڼ�����(ע��������0��ʼ)
** @param color ���µ���ɫ
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
** @berf: ��������ʱ��
** @param UpdateLEDStartIndex LED��ʼ������
** @param UpdateLEDNum ���θ��¶��ٸ���
** @param DisColorTab ��ʾ����ɫ��
** @param DisColorTabSize ��ʾ��ɫ��Ĵ�С
** @param UpdateDisFlag ������ʾ��־ 1��ʼ���� 0������
** @param resetFlag ��λ��־ 1��Ҫ��λ 0����Ҫ (���費��Ҫ��ͷ��ʼ����)
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
** @berf: ʵ�ʸ��µ���ɫ������ɫͬ����LED�ϣ�
** @param null
** @return: null
*/
void LED_Ic_Handle(void)
{
		if(ledIcWrtieEn == 0 || ledIcWrtieCurrentCnt > UpdateLEDIcNum  || ledIcWrtieCurrentCnt > IC_RGB_BUFF_SIZE)
		{
			return;
		}

		// һ�η�1���Ƶ����ݣ��Ը�������������ִ��ʱ��
		led_rgb_driver(stLEDBright[ledIcWrtieCurrentCnt], stLEDBright[ledIcWrtieCurrentCnt+1], stLEDBright[ledIcWrtieCurrentCnt+2]);
		ledIcWrtieCurrentCnt+=3;
}


void LED_SetPwm(u8 led, u8 brightness)
{
	/*
	if(led%3==1)	//green ���Ƚ���
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
**	@bref:���ú�������
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
*������    : LedIcAllOff
*��������  : �Ƶ���ʾ���ú���
*��������  : u8 breDutyVal--ռ�ձ�
*��������ֵ: void
*��������  : 
*/
void    LedIcAllOff(void)
{
    static u8 i;
    if(flash_led_data==0)
		{
        flash_led_data=1;       //ֻ��һ��
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

// �������н�LED ICȫ������Ϊһ����ɫ
void    LedIcColorUpdateAll(u32 color)
{
    static u8 i;
    if(flash_led_data==0)
		{
        flash_led_data=1;       //ֻ��һ��
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
*��������  : �Ƶ���ʾ���ú���
*��������  : LEDUpdateStart ��ʼ����λ��
*@param: ColorTab ��Ҫ���µ���ɫ��
*@param: size ���µĴ�С
*��������ֵ: void
*/
void LedIcColorUpdate(u8 LEDUpdateStart, u8 *ColorTab,u8 size,u8 updateLedNum)
{
    static u8 i;
    if(flash_led_data==0)
		{
        flash_led_data=1;       //ֻ��һ��
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
*������    : LedDispSel
*��������  : �Ƶ���ʾ���ú���
*��������  : u8 breDutyVal--ռ�ձ�
*��������ֵ: void
*��������  : 
==============================================================================*/
void 	LedDispSel(u8 breDutyVal)
{
	static u8 i;

	if(flash_led_data==0)
	{
			flash_led_data=1;       //ֻ��һ��

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
*������    : LedBreDispSel
*��������  : ��������ʾ���ú���
*��������  : void
*��������ֵ: void
*��������  : 
==============================================================================*/

void 	LedBreDispSel(u8 breDutyVal)
{
	static u8 i;
	if(flash_led_data==0)
	{
			flash_led_data=1;       //ֻ��һ��
      
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


/* ��˸/�����ж� */
void 	LedHand(void)
{
	if(ledFlaBreFlag == 0)
		LedFlaDeal();       //��˸����
	else
		LedBreDeal();       //��������
}


/************************************************************************
 *������:LedFlaSet
 *��������:LED��˸����
 *�������:
 			(1)dispBitMap:bit0:Red	bit1:Green	bit2:Blue
 			(2)onTime:����ʱ��:onTime*��˸ִ�к�����������
 			(3)offTime:���ʱ��:offTime*��˸ִ�к�����������
 			(4)flaCnt:��˸����(���������)
 			(5)delTimeCnt:��˸֮ǰ���׼��ʱ��:delTimeCnt*��˸ִ�к�����������
 *���ز���:��
 *��������:��
 *    ע������:	(1)���������ʱ��Ϊ255*��˸ִ�к�����������
 				(2)��������ʱ��Ϊ255*��˸ִ�к�����������
 				(3)�������dispBitMap==0xff,��dispBitMap���ֲ���
 				(4)���flaCnt>=100,��������˸��ȥֱ��ǿ�ƹر���˸
************************************************************************/
void LedFlaSet(u64 dispBitMap,u8 onTime,u8 offTime,u8 flaCnt,u8 delTimeCnt)
{
	   run_led_bit=0;
	   run_led_15ms=0;

    flash_led_data=0;
//    if(dispBitMap!=0xff)
    ledDispBitMap=dispBitMap;   //ѡ���Ӧ�ĵ�
    ledOnTime=onTime;               //����ʱ��
    ledOffTime=offTime;             //���ʱ��
    ledFlaCnt=flaCnt;               //��˸����
    ledDispDelCnt=delTimeCnt;       //��˸֮ǰ���׼��ʱ��

    ledOnTimeCnt=0;
    ledOffTimeCnt=0;

    ledFlaBreFlag=false;
    ledBreDuty=0;
}


/*************************************************************
 *������:LedFlaHand
 *��������:LED ��˸/����/����ִ�к���,����10msʱ����ִ��
 *�������:��
 *���ز���:��
 *��������:��
 *    ע������:	(1)��Ҫʹ��ledFlaBreFlagѡ��ִ��
 					false:��˸����
 					true:��������
 				(2)�˺����ĵ��������趨Ϊ10ms,���������ʱ��
 				�ɴﵽ655s,�����Ҫ���������ƿ�������ӱ�������
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
    else 	if(ledOnTime>0 && ledOffTime==0)			//����
    {
        LedDispSel(LED_BRE_PERI_MAX);
    }
    else 	if(ledFlaCnt)                               //��˸
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
 *������:LedBreRea
 *��������:LED����׼�����ú���
 *�������:	dispBitMap:bit0:Red	bit1:Green	bit2:Blue
 			upTime:������������,����ʱ��Ϊ:upTime*������������
 			downTime:�½���������,�½�ʱ��Ϊ:downTime*������������
 			breCnt:������������
 			breDir:�����ķ���:ָ����ʼ�����ķ��� 0:������1:����
            dutyKeepFlag:�Ƿ񱣳�ԭռ�ձ� 0:�������ã�1:����ԭռ�ձ�
 *���ز���:��
 *��������:��
 *    ע������:	(1)���dispBitMap==0xff,��ledDispBitMap���ֲ���
 				(2)upTime��downTime��ʱ��Ϊ10ms
 				(3)���಻�ٽ��м���,�����Լ�����Ҫ����ô��뼴��
					,Ŀ���Ǳ����������,��ʡ�ռ�
 				(4)�����ʼ�����ķ�������,�����ú�������ʱ�轫
 					��Ҫ�ĺ�������-1
*************************************************************/
void LedBreRea(u64 dispBitMap,u8 upTime,u8 downTime,u8 breCnt,u8 breDir,u8 i)
{
    flash_led_data=0;
//    if(dispBitMap!=0xff)
        ledDispBitMap=dispBitMap;

    ledBreDir[i]=breDir;       //breDir:�����ķ���
    if(ledBreDir[i]==false)
        BreDuty[i]=LED_BRE_PERI_MIN;
    else
    {
        BreDuty[i]=LED_BRE_PERI_MAX;
    }
    ledBreCnt[i]=breCnt;                   //breCnt:������������

    //@@�����������
    ledBreUpStepLenSet=upTime;          //��������
    //@@�½��������
    ledBreDownStepLenSet=downTime;      //���𲽾�

    ledFlaBreFlag=true;
}

/**
 *������:LedBreDeal
 *��������:����ִ�к���
 *�������:��
 *���ز���:��
 *��������:��
 *    ע������:	(1)�˺�����ִ�е�������Ϊ10ms
				(2)���ledBreCnt>=100,�������᲻ִͣ����ȥֱ��
					ǿ��ֹͣ
				(3)�������������ߺ��������Ϊ1��,���Ժ�������
					��Ҫ���м���
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
            if(BreDuty[i]<LED_BRE_PERI_MAX-ledBreUpStepLenSet)//ledBreUpStepLenSet��������
                BreDuty[i]+=ledBreUpStepLenSet;
            else
            {
                BreDuty[i]=LED_BRE_PERI_MAX;        //ledBreDutyռ�ձ�
                if(ledBreCnt[i]<100 && ledBreCnt[i])      //ledBreCnt��������
                    ledBreCnt[i]--;
                if(ledBreCnt[i])
                    ledBreDir[i]=true;                 //breDir��������
            }
        }
        else
        {
            //@@ԭʼ����
            if(BreDuty[i]>ledBreDownStepLenSet)     //ledBreDownStepLenSet�½�����
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
		LedBreDispSel(BreDuty[i]);     //�Ƶ���ʾ���ú���
}

#endif
