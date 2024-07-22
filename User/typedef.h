#ifndef _TYPEDEF_H
#define _TYPEDEF_H

// #define KEY_USE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define    MOS_PORT              GPIOA
#define    MOS_PIN               LL_GPIO_PIN_3

#define    HEAT_PORT             GPIOA
#define    HEAT_PIN              LL_GPIO_PIN_4

#define    MOS1_PORT              GPIOC
#define    MOS1_PIN               LL_GPIO_PIN_1

#define    HEAT1_PORT             GPIOC
#define    HEAT1_PIN              LL_GPIO_PIN_0

#ifdef KEY_USE
	#define    KEY_PORT              GPIOA
	#define    KEY_PIN               LL_GPIO_PIN_5
#endif

/**********************SWITCH DIP**************************/
#define		 SWITCH_DIP_PORT		 GPIOB
#define		 SWITCH_DIP_PIN		 	 LL_GPIO_PIN_0

#define		 SWITCH_DIP_EN_PORT		 GPIOB
#define		 SWITCH_DIP_EN_PIN		 LL_GPIO_PIN_7

/********************** USB ******************************/
#define    USB_PORT              GPIOA
#define    USB_PIN               LL_GPIO_PIN_7

#define    CHRG_PORT             GPIOA
#define    CHRG_PIN              LL_GPIO_PIN_5

#define    CHRG_EN_PORT          GPIOA
#define    CHRG_EN_PIN           LL_GPIO_PIN_6

// 充电使能控制
#define    CHRG_ENABLE          	LL_GPIO_ResetOutputPin(CHRG_EN_PORT,CHRG_EN_PIN);
#define    CHRG_DISABLE           LL_GPIO_SetOutputPin(CHRG_EN_PORT,CHRG_EN_PIN);

#define    SDA_PORT         GPIOA
#define    SDA_PIN          LL_GPIO_PIN_4

#define    SCL_PORT         GPIOA
#define    SCL_PIN          LL_GPIO_PIN_5

#define SDA_MODE(value) \
    ((value) ? LL_GPIO_SetPinMode(SDA_PORT,SDA_PIN,LL_GPIO_MODE_OUTPUT): LL_GPIO_SetPinMode(SDA_PORT,SDA_PIN,LL_GPIO_MODE_INPUT))

#define SDA(value) \
    ((value) ? LL_GPIO_SetOutputPin(SDA_PORT, SDA_PIN) : LL_GPIO_ResetOutputPin(SDA_PORT, SDA_PIN))

#define SCL(value) \
    ((value) ? LL_GPIO_SetOutputPin(SCL_PORT,SCL_PIN) : LL_GPIO_ResetOutputPin(SCL_PORT,SCL_PIN))

#define   SDA_Value    LL_GPIO_IsInputPinSet(SDA_PORT,SDA_PIN)

/********************** LED IC DI **************************/
#define    LED_SING_PORT        GPIOA
#define    LED_SING_PIN         LL_GPIO_PIN_0  

#define    LED_PWR_EN_PORT        GPIOA
#define    LED_PWR_EN_PIN         LL_GPIO_PIN_1  

#define    MIC_PORT             GPIOB
#define    MIC_PIN              LL_GPIO_PIN_1



#define    BAT_CHANNEL         9
#define    OUT_CHANNEL         2
#define    OUT1_CHANNEL        5
#define    USB_CHANNEL         4
#define    SWITCH_CHANNEL      7



#define    KEY_IO              LL_GPIO_IsInputPinSet(KEY_PORT,KEY_PIN)
#define    HEAT_IO             LL_GPIO_IsInputPinSet(HEAT_PORT,HEAT_PIN)
#define    MIC_IO              LL_GPIO_IsInputPinSet(MIC_PORT,MIC_PIN)
#define    CHRG_IO             LL_GPIO_IsInputPinSet(CHRG_PORT,CHRG_PIN)  
#define    USB_IO              LL_GPIO_IsInputPinSet(USB_PORT,USB_PIN)
#define    SWITCH_IO           LL_GPIO_IsInputPinSet(SWITCH_DIP_PORT,SWITCH_DIP_PIN)



#define   MOS_ON               {LL_GPIO_ResetOutputPin(MOS_PORT,MOS_PIN);  }
#define   MOS_OFF              {LL_GPIO_SetOutputPin(MOS_PORT,MOS_PIN);    }
#define   MOS1_ON              {LL_GPIO_ResetOutputPin(MOS1_PORT,MOS1_PIN);  }
#define   MOS1_OFF             {LL_GPIO_SetOutputPin(MOS1_PORT,MOS1_PIN);    }


#endif

