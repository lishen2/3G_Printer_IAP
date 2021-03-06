#ifndef _ONCHIP_FLASH_H_
#define _ONCHIP_FLASH_H_

#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif

/* ������д��Ƭ��flash */
int FLASH_Write(u32 addr, void* buf, int size);
int FLASH_Erase(u32 addr, u32 size);

#endif

