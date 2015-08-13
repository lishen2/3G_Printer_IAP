#include <stdlib.h>
#include "stm32f10x.h"
#include "utils.h"
#include "update.h"
#include "ff.h"
#include "platform.h"
#include "onchip_flash.h"

#define UP_PROGRAME_FILENAME  "update.bin"

/* ȫ���ļ�ϵͳ */
static FATFS g_fs;

/* �����ļ� */
static FIL g_updateFile;

/* ��дflash�Ļ����� */
static u8 g_readBuf[FLASH_PAGE_SIZE];

int _openAndUpdate(void)
{
   	FRESULT res;
    u32 readSize;
	int ret;
	u32 addr;

    /* �������ļ� */    
    res = f_open(&g_updateFile, UP_PROGRAME_FILENAME, FA_READ);
    if (FR_OK != res){
        return ERROR_FAILED;
    }

	/* ����Ƭ��flash */
	ret = FLASH_Erase(PLATFORM_FLASH_PROGRAME_START, f_size(&g_updateFile));
	if (FLASH_COMPLETE != ret){
		return ERROR_FAILED;
	}

    /* ��ȡ�ļ� */
	ret = ERROR_SUCCESS;
	addr = PLATFORM_FLASH_PROGRAME_START;
    while(1){
        res = f_read(&g_updateFile, g_readBuf, sizeof(g_readBuf), &readSize);
		if (FR_OK != res){
			ret = ERROR_FAILED;
			break;
		}
		
		ret = FLASH_Write(addr, g_readBuf, readSize);
		if (ERROR_SUCCESS != ret){
			ret = ERROR_FAILED;
			break;
		} 

		addr += readSize;

        if (readSize < sizeof(g_readBuf)){
            break;
        }
    }
    
    /* �ر��ļ� */
    f_close(&g_updateFile);

    return ERROR_SUCCESS;
}

int UP_TryUpdate(void)
{
	FRESULT res;
	int ret;

	/* �����ļ�ϵͳ */
	res = f_mount(&g_fs, "", 1);    
	if (FR_OK == res){
	
		/* ���Դ򿪲���ȡ�ļ� */
		FLASH_Unlock();
		ret = _openAndUpdate();
		FLASH_Lock();

		f_mount(NULL, "", 0);

	} else {
		ret = ERROR_FAILED;
	}

	return ret;
}

