#ifndef _CONFIG_H_
#define _CONFIG_H_

/* �����ļ��и��ֶγ��� */
#define CONF_APN_LENGTH         16
#define CONF_ADDRESS_LENGTH     64

/* ��ʼ������ */
void CONF_InitConfig(void);

/* �����Ƿ���� */
int CONF_IsUpdated(void);

/* ��ȡ���� */
char* CONF_GetAddress(void);
u16 CONF_GetPort(void);
char* CONF_GetAPN(void);

#endif

