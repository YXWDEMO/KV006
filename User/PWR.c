#include "main.h"

void iwdg_init(void)
{
	 /* Enable LSI */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() == 0U) {;}
  /* Enable IWDG */
  LL_IWDG_Enable(IWDG);
  /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers */
  LL_IWDG_EnableWriteAccess(IWDG);
  /* Set IWDG prescaler */
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_32); /* T=1MS */
	//最大4095
  LL_IWDG_SetReloadCounter(IWDG, 3000); /* 1ms*3000=3s */
  /* Check if all flags Prescaler, Reload & Window Value Update are reset or not */
  while (LL_IWDG_IsReady(IWDG) == 0U) {;}
  //喂狗
  LL_IWDG_ReloadCounter(IWDG);
}

//修改选项字节，包括BOR,IWDG，NRST等
void option_init(void)
{
	//注意设置判断修改条件，防止出现一直修改复位
	 if((READ_BIT(FLASH->OPTR, OB_USER_SWD_NRST_MODE)!= OB_SWD_PB6_GPIO_PC0)|| (READ_BIT(FLASH->OPTR, OB_USER_BOR_EN)!= OB_BOR_ENABLE)|| (READ_BIT(FLASH->OPTR, OB_USER_BOR_LEV)!= OB_BOR_LEVEL_2p5_2p6))
  {
		FLASH_OBProgramInitTypeDef OBInitCfg={0};
		/* Unlock the Flash to enable the flash control register access */
		HAL_FLASH_Unlock();
		/* Unlock the Flash to enable access to the part of flash control register that is about option byte */
		HAL_FLASH_OB_Unlock();
		/* Initialize FLASH Option Bytes PROGRAM structure */
		OBInitCfg.OptionType = OPTIONBYTE_USER;
		OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_IWDG_SW | OB_USER_SWD_NRST_MODE;
		OBInitCfg.USERConfig = OB_BOR_ENABLE | OB_BOR_LEVEL_2p5_2p6 | OB_IWDG_SW | OB_IWDG_SW | OB_SWD_PB6_GPIO_PC0 ;
		/* Execute option byte program */
		HAL_FLASH_OBProgram(&OBInitCfg);
		/* Lock the Flash to disable the flash control register access */
		HAL_FLASH_Lock();
		/* Lock the Flash to disable access to the part of flash control register that is about option byte */
		HAL_FLASH_OB_Lock();
		/* Generate a reset and let option byte reload */
		HAL_FLASH_OB_Launch();
  }
	
}

void pwr_init_jcq(void)
{
	__disable_irq();
	if(READ_BIT(FLASH->OPTR, OB_USER_SWD_NRST_MODE)!= OB_SWD_PB6_GPIO_PC0)
	{
		WRITE_REG(FLASH->KEYR, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_KEY2);
		
		WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY1);
    WRITE_REG(FLASH->OPTKEYR, FLASH_OPTKEY2);
		if(!READ_BIT(FLASH->SR,FLASH_SR_BSY))
		{
			FLASH->TS0  = (*(uint32_t *)0x1FFF011C)&0x1FF;           
			FLASH->TS1  = ((*(uint32_t *)(0x1FFF011C))>>18)&0x3FF;    
			FLASH->TS3  = (*(uint32_t *)(0x1FFF011C)>>9)&0x1FF;      
			FLASH->TS2P = (*(uint32_t *)0x1FFF0120)&0x1FF;           
			FLASH->TPS3 = ((*(uint32_t *)0x1FFF0120)>>16)&0xFFF;    
			FLASH->PERTPE = (*(uint32_t *)0x1FFF0124)&0x3FFFF;      
			FLASH->SMERTPE = (*(uint32_t *)0x1FFF0128)&0x3FFFF;     
			FLASH->PRGTPE = (*(uint32_t *)0x1FFF012C)&0xFFFF;       
			FLASH->PRETPE = ((*(uint32_t *)0x1FFF012C)>>16)&0x3FFF;
			
			FLASH->OPTR=0x0000DEAA;	//这里只修改了PC0，其他不变
			
			FLASH->CR|=FLASH_CR_OPTSTRT;
			FLASH->CR|=FLASH_CR_EOPIE;

			*((__IO uint32_t *)(0x40022080))=0xff;
			while(READ_BIT(FLASH->SR,FLASH_SR_BSY));
			
			FLASH->SR=0x00008011;
			
			
		}
		SET_BIT(FLASH->CR, FLASH_CR_LOCK);
		SET_BIT(FLASH->CR, FLASH_CR_OPTLOCK);
		SET_BIT(FLASH->CR, FLASH_CR_OBL_LAUNCH);
	}
	__enable_irq();
}


