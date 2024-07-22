#include "main.h"

//static uint8_t FlashEraseFlag = 1;
//static uint8_t FlashWriteCnt = 0;
uint32_t UserData[32] = {0x00};


//擦除
void Flash_Erase(uint8_t size)
{
	uint8_t nbPages = 0;

	if(size<FLASH_PAGE_SIZE)
	{
		nbPages = 1;
	}else{
		nbPages = size / FLASH_PAGE_SIZE;
	}
	
	HAL_FLASH_Unlock();

	uint32_t PAGEError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct={0};

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;                                     /* Macro FLASH_TYPEERASE_PAGEERASE means Page erase , Macro FLASH_TYPEERASE_SECTORERASE means Sector erase */
  EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;                                         /* Start address of erase area */
  EraseInitStruct.NbPages  = nbPages;                               /* Number of pages to be erased */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)                               /* Perform page erase,PAGEError save faulty page in case of error(0xFFFFFFFF means that all the pages have been correctly erased) */
  {
		
  }
}

//查空
void Flash_Blank(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(UserData))
  {
    if (0xFFFFFFFF != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      Flash_Erase(FLASH_PAGE_SIZE);
    }
    addr += 4;
  }
}

//写
void Flash_Program(uint32_t *userData, uint8_t size)
{
	uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* Start address of user write flash */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + size);                  /* End address of user write flash */
  uint32_t *src = userData;                                                     /* Pointer to array */

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)  /* Perform Program */
    {
      flash_program_start += FLASH_PAGE_SIZE;                                           /* Point to the start address of the next page to be written */
      src += FLASH_PAGE_SIZE / 4;                                                       /* Point to the next UserData to be written */
    }
  }
	HAL_FLASH_Lock();
}

//校验
int8_t Flash_Verity(uint32_t *userData, uint8_t size)
{
	 uint32_t addr = 0;

  while (addr < size)
  {
    if (userData[addr / 4] != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
			return -1;
    }
    addr += 4;
  }
	
	return 0;
}


void flash_Write_User_Data(uint32_t *userData, uint8_t size)
{
//	if(FlashWriteCnt >= (FLASH_PAGE_SIZE/size))
//	{
//		FlashWriteCnt = 0;
//		FlashEraseFlag = 1;
//	}

//	if(FlashEraseFlag)
//	{
//		FlashEraseFlag = 0;
		Flash_Erase(size);
//	}

//	FlashWriteCnt+=2;

	//Flash_Blank();
	Flash_Program(userData,size);
	Flash_Verity(userData,size);
}

void flash_Read_User_Data(uint32_t* userData)
{
	userData[0] = HW32_REG(FLASH_USER_START_ADDR);
	userData[1] = HW32_REG(FLASH_USER_START_ADDR + 4);
}
