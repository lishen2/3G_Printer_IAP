#include <string.h>
#include "stm32f10x.h"
#include "onchip_flash.h"
#include "utils.h"
#include "assert.h"

#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif

/* stm32f103����64kb��flash��
   ��Ϊ������60KB���ڴ�ų���
   ����4KB���ڴ���������� */
#define FLASH_DATA_LENGTH         0x1000   

/* flash�����ڴ�����ݵ�λ��, START_ADDRESS + 60KB */
#define FLASH_DATA_START_ADDRESS  (0x8000000 + 0xF000)

/* ��Ƭ��flash�ж�ȡ���� */
int FLASH_Read(void* buf, int bufsize){
	
	ASSERT(bufsize <= FLASH_DATA_LENGTH);

	memcpy(buf, (void*)FLASH_DATA_START_ADDRESS, bufsize);

	return ERROR_SUCCESS;
}

/* ������д��Ƭ��flash */
int FLASH_Write(void* buf, int bufsize)
{
	int i, retry;
	FLASH_Status status;
	u32 des_addr, src_addr;

	int ret = ERROR_SUCCESS;

	ASSERT(bufsize <= FLASH_DATA_LENGTH);

    /* ����flash */
    FLASH_UnlockBank1();

	/* ����ҳ */
	i = 0;
	retry = 0;
	while (1){
		des_addr = FLASH_DATA_START_ADDRESS + (FLASH_PAGE_SIZE * i);	

		status = FLASH_ErasePage(des_addr);
		if (FLASH_COMPLETE == status){
			i++;
			retry = 0;
		} else {
		 	retry++;
		}

		if (retry > 5 || FLASH_PAGE_SIZE * i >= bufsize){
			break;
		}
	}

	if (retry > 5){
		ret = ERROR_FAILED;
	}

	/* д������
	   ԭ���ݲ�Ϊ�ֶ���ʱ��д�����ݲ�����ԭ�����£�
	   1����һ����������д��falsh�����в���Ӱ�죬��ȡ��ʱ���ǰ����ֽڶ�ȡ�ģ���д������ݲ��ᱻ������
	   2��STM32û���ڴ����Խ���飬����Խ������ڴ�Ӧ�ò����������
	   3������flash�б���һ������
	 */
	retry = 0;
	des_addr = FLASH_DATA_START_ADDRESS;
	src_addr = (u32)buf;
	while(1){
		status = FLASH_ProgramWord(des_addr, *((u32*)src_addr));
		if (FLASH_COMPLETE == status){
			src_addr += 4;
			des_addr += 4;
			retry = 0;
		} else {
		 	retry++;
		}
		
		if (retry > 5 || src_addr >= ((u32)buf + bufsize)){
			break;
		}	
	}

	if (retry > 5){
		ret = ERROR_FAILED;
	}

	/* �������� */
	FLASH_LockBank1();

	return ret;
}

