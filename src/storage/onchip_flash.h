#ifndef _ONCHIP_FLASH_H_
#define _ONCHIP_FLASH_H_

/* ��Ƭ��flash�ж�ȡ���� */
int FLASH_Read(void* buf, int bufsize);

/* ������д��Ƭ��flash */
int FLASH_Write(void* buf, int bufsize);

#endif

