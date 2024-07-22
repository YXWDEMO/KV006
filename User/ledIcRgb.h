#ifndef _LED_H
#define _LED_H
#if 0
///*========包含头文件========*/
//#include "yxw_xx.h"
//#include "bsp_config.h"
//#include "bsp_delay.h"
//#include "user.h"

/*================宏定义================*/
////@@此处如果选择对应的灯,则ledDispBitMap与对应的宏"|"运算
//	//如果屏蔽(不选择)对应的灯,则ledDispBitMap与对应的宏"&"运算
//跑马灯 8个TRGB
#define		LED_R0_SEL		0x01
#define		LED_G0_SEL		0x02
#define		LED_B0_SEL		0x04
#define		LED_W0_SEL		0x07

#define		LED_R1_SEL		0x08
#define		LED_G1_SEL		0x10
#define		LED_B1_SEL		0x20
#define		LED_W1_SEL		0x38

#define		LED_R2_SEL		0x40
#define		LED_G2_SEL		0x80
#define		LED_B2_SEL		0x100
#define		LED_W2_SEL		0x1C0

#define		LED_R3_SEL		0x200
#define		LED_G3_SEL		0x400
#define		LED_B3_SEL		0x800
#define		LED_W3_SEL		0xE00

#define		LED_R4_SEL		0x1000
#define		LED_G4_SEL		0x2000
#define		LED_B4_SEL		0x4000
#define		LED_W4_SEL		0x7000




#define		LED_ALL_R_SEL	(LED_R0_SEL+LED_R1_SEL+LED_R2_SEL+LED_R3_SEL+LED_R4_SEL)
#define		LED_ALL_G_SEL	(LED_G0_SEL+LED_G1_SEL+LED_G2_SEL+LED_G3_SEL+LED_G4_SEL)
#define		LED_ALL_B_SEL	(LED_B0_SEL+LED_B1_SEL+LED_B2_SEL+LED_B3_SEL+LED_B4_SEL)
#define		LED_ALL_W_SEL	 (LED_ALL_R_SEL+LED_ALL_G_SEL+LED_ALL_B_SEL)


#define		LED_R5_SEL		0x8000
#define		LED_G5_SEL		0x10000
#define		LED_B5_SEL		0x20000
#define		LED_W5_SEL		0x38000

#define		LED_R6_SEL		0x40000
#define		LED_G6_SEL		0x80000
#define		LED_B6_SEL		0x100000
#define		LED_W6_SEL		0x1C0000

#define		LED_R7_SEL		0x200000
#define		LED_G7_SEL		0x400000
#define		LED_B7_SEL		0x800000
#define		LED_W7_SEL		0xE00000

//按键档位指示灯 4个TRGB
#define		LED_R8_SEL		0x1000000
#define		LED_G8_SEL		0x2000000
#define		LED_B8_SEL		0x4000000
#define		LED_W8_SEL		0x7000000

#define		LED_R9_SEL		0x8000000
#define		LED_G9_SEL		0x10000000
#define		LED_B9_SEL		0x20000000
#define		LED_W9_SEL		0x38000000

#define		LED_R10_SEL		0x40000000
#define		LED_G10_SEL		0x80000000
#define		LED_B10_SEL		0x100000000
#define		LED_W10_SEL		0x1C0000000

#define		LED_R11_SEL		0x200000000
#define		LED_G11_SEL		0x400000000
#define		LED_B11_SEL		0x800000000
#define		LED_W11_SEL		0xE00000000

#define		LED_SIDE_R_SEL	0x249249
#define		LED_SIDE_G_SEL	0x492492
#define		LED_SIDE_B_SEL	0x924924
#define		LED_SIDE_Y_SEL	0x6DB6DB
#define		LED_SIDE_W_SEL	0xFFFFFF

#define		LED_KEY_R_SEL	0x249000000
#define		LED_KEY_G_SEL	0x492000000
#define		LED_KEY_B_SEL	0x924000000
#define		LED_KEY_Y_SEL	0x6DB000000
#define		LED_KEY_W_SEL	0xFFF000000

//#define		LED_ALL_R_SEL	0x249249249
//#define		LED_ALL_G_SEL	0x492492492
//#define		LED_ALL_B_SEL	0x924924924
//#define		LED_ALL_Y_SEL	0x6DB6DB6DB
//#define		LED_ALL_W_SEL	0xFFFFFFFFF

//@@此处服务使用软件模拟PWM的情况(正常情况下不使用)
#define		LED_R_ON		LL_GPIO_ResetOutputPin(GPIOB,LL_GPIO_PIN_3)
#define		LED_R_OFF		LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_3)

#define		LED_G_ON		pwm_set_duty(LED_G_PWM, LED_BRE_PERI_MIN)
#define		LED_G_OFF		pwm_set_duty(LED_G_PWM, LED_BRE_PERI_MAX)

#define		LED_B_ON		LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_1)
#define		LED_B_OFF		LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_1)


#define		LED_BRE_PERI_MIN		0
#define		LED_BRE_PERI_MAX		255

//按键档位指示灯 4个TRGB 跑马灯 8个TRGB
//#define		LED_KEY_CTRL_ON     led_flag=1;led_key_flag=1
//#define		LED_CTRL_ON         led_flag=1;led_key_flag=0
//#define		KEY_CTRL_ON         led_key_flag=1;led_flag=0

#define RGB_RED 	0xff0000
#define RGB_GREEN 0x00ff00
#define RGB_BLUE 	0x0000ff

// IC灯个数
#define IC_RGB_BUFF_SIZE 84 //IC个数对应RGB颜色缓存大小
#define IC_RGB_NUM 28 //IC个数
#define IC_RGB_LOGO_NUM 6 //logo IC个数 
#define DYNAMIC_LED_IC_NUM 22 
#define DYNAMIC_LED_IC_SETUP_NUM 1 //步进

#define LED_IC_DI_HIGH GPIOA->BSRR = (1<<0)
#define LED_IC_DI_LOW  GPIOA->BRR  = (1<<0)

/// 0 1码元
#define LED_SEND2_BIT1()                            \
{                                                   \
    LED_IC_DI_HIGH;                           \
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    LED_IC_DI_LOW;                            \
    __nop();__nop();__nop();                        \
}

#define LED_SEND2_BIT0()                            \
{                                                   \
    LED_IC_DI_HIGH;                           			\
    __nop();__nop();__nop();                        \
		LED_IC_DI_LOW;                            					\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
}

#define LED_SEND_BIT1()                             \
{                                                   \
    LED_IC_DI_HIGH;                           					\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    LED_IC_DI_LOW;                            					\
    __nop();__nop();__nop();                        \
}

#define LED_SEND_BIT0()                             \
{                                                   \
    LED_IC_DI_HIGH;                           					\
    __nop();__nop();__nop();                        \
    LED_IC_DI_LOW;                            					\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
    __nop();__nop();__nop();__nop();__nop();__nop();\
}


#define LED_SEND_RESET()                            \
{                                                   \
    LED_IC_DI_LOW;																			\
		LL_mDelay(1);																\
}

extern u8 LEDBuff[3];
#define LED_BUFF_BIT0	LEDBuff[0]&0x01//.bits.bit0
#define LED_BUFF_BIT1	LEDBuff[0]&0x02//.bits.bit1
#define LED_BUFF_BIT2	LEDBuff[0]&0x04//.bits.bit2
#define LED_BUFF_BIT3	LEDBuff[0]&0x08//.bits.bit3
#define LED_BUFF_BIT4	LEDBuff[0]&0x10//.bits.bit4
#define LED_BUFF_BIT5	LEDBuff[0]&0x20//.bits.bit5
#define LED_BUFF_BIT6	LEDBuff[0]&0x40//.bits.bit6
#define LED_BUFF_BIT7	LEDBuff[0]&0x80//.bits.bit7
#define LED_BUFF_BIT8	LEDBuff[1]&0x01//.bits.bit0
#define LED_BUFF_BIT9	LEDBuff[1]&0x02//.bits.bit1
#define LED_BUFF_BIT10	LEDBuff[1]&0x04//.bits.bit2
#define LED_BUFF_BIT11	LEDBuff[1]&0x08//.bits.bit3
#define LED_BUFF_BIT12	LEDBuff[1]&0x10//.bits.bit4
#define LED_BUFF_BIT13	LEDBuff[1]&0x20//.bits.bit5
#define LED_BUFF_BIT14	LEDBuff[1]&0x40//.bits.bit6
#define LED_BUFF_BIT15	LEDBuff[1]&0x80//.bits.bit7
#define LED_BUFF_BIT16	LEDBuff[2]&0x01//.bits.bit0
#define LED_BUFF_BIT17	LEDBuff[2]&0x02//.bits.bit1
#define LED_BUFF_BIT18	LEDBuff[2]&0x04//.bits.bit2
#define LED_BUFF_BIT19	LEDBuff[2]&0x08//.bits.bit3
#define LED_BUFF_BIT20	LEDBuff[2]&0x10//.bits.bit4
#define LED_BUFF_BIT21	LEDBuff[2]&0x20//.bits.bit5
#define LED_BUFF_BIT22	LEDBuff[2]&0x40//.bits.bit6
#define LED_BUFF_BIT23	LEDBuff[2]&0x80//.bits.bit7


typedef enum{
	Water_Lamps_Dir_None,
	Water_Lamps_Dir_Up,
	Water_Lamps_Dir_Down,
	Water_Lamps_Dir_Loop,
}LEDIcRunDir_t;

extern u8 run_led_bit;
extern u8 run_led_15ms;

extern u8	stLEDBright[IC_RGB_BUFF_SIZE];
extern u8 Smoke_Dis_Color_Tab[66];
extern const u8 Clr_Color_Tab[];
extern const u8 Err_Color_Tab[];

/*================函数声明================*/
extern void 	LedIcAllOff(void);
extern void 	LedDispSel(u8 breDutyVal);
//void 	LedBreDispSel(u8 dispBitMap,u8 duty);
extern void 	LedBreDispSel(u8 breDutyVal);
extern void 	LedHand(void);
extern void 	LedFlaDeal(void);
extern void 	LedBreDeal(void);
extern void		LedBreExe(void);

extern void		LedFlaSet(unsigned long long dispBitMap,u8 onTime,u8 offTime,u8 flaCnt,u8 delTimeCnt);
extern void 	LedBreRea(u64 dispBitMap,u8 upTime,u8 downTime,u8 breCnt,u8 breDir,u8 dutyKeepFlag);

extern void 	LED_Ic_Handle(void);

extern void set_led_hx(void);
extern void set_bre_data(void);

extern u8*  GetWattLogoColorTab(u8 wattLevel);
extern u8*  GetWattGearsColorTab(u8 wattLevel);
extern void LedIcColorUpdate(u8 LEDUpdateStart, u8 *ColorTab,u8 size,u8 updateLedNum);
extern void LedIcColorUpdateAll(u32 color);
extern void SetflashLedDataFlag(void);
extern void SetLEDIcRunParam(u8 UpdateLEDStartIndex, u8 UpdateLEDNum, u8 DisLEDNum,u8* DisColorTab, u8 DisColorTabSize, u8 UpdateDisFlag,u8 resetFlag);
extern void SetUpdateLEDIcNum(u8 DisLEDNum);
#endif
#endif

