#ifndef _PLATFORM_H_
#define _PLATFORM_H_

//flash物理地址
#define PLATFORM_FLASH_PHY_ADDR 0x8000000
#define PLATFORM_FLASH_PHY_SIZE (64 * 1024)		//64k

//IAP分配8KB
#define PLATFORM_FLASH_IAP_START 	   PLATFORM_FLASH_PHY_ADDR
#define PLATFORM_FLASH_IAP_SIZE        (16 * 1024)

//应用分配44KB
#define PLATFORM_FLASH_PROGRAME_START  (PLATFORM_FLASH_IAP_START + PLATFORM_FLASH_IAP_SIZE)
#define PLATFORM_FLASH_PROGRAME_SIZE   (44 * 1024)

//配置分配4KB
#define PLATFORM_FLASH_CONF_START      (PLATFORM_FLASH_PROGRAME_START + PLATFORM_FLASH_PROGRAME_SIZE)
#define PLATFROM_FLASH_CONF_SIZE	   (4 * 1024)

#endif

