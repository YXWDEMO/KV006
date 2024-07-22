#ifndef __SWITCH_DIP_H__
#define __SWITCH_DIP_H__

#include "user.h"

#ifdef __SWITCH_DIP_C__
	#define SWITCH_DIP_EXT 
#else
	#define SWITCH_DIP_EXT extern
#endif

enum{
	SW_GERAS_L0,
	SW_GERAS_L1,
	SW_GERAS_L2,
};
	
typedef struct{
	u8 swGeras;// 拨码开关档位
	u8 swGerasOld;// 拨码开关上次档位
}SwitchDipInfo_t;


SWITCH_DIP_EXT SwitchDipInfo_t swInfo;

SWITCH_DIP_EXT void 	Switch_Init(void);
SWITCH_DIP_EXT void 	Switch_Scan(void);

#endif
