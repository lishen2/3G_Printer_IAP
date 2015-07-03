#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"
#include "utils.h"
#include "config.h"
#include "conf_parser.h"
#include "ff.h"
#include "assert.h"
#include "onchip_flash.h"

#define CONF_CONFIG_FLAG  0x4321 

#define CONF_CONFIG_FILENAME  "config.ini"

/* �����ļ��е�������Ϣ���� */
#define CONF_KEY_APN          "ACCESS_POINT_NAME"
#define CONF_KEY_ADDRESS      "SERVER_ADDRESS"
#define CONF_KEY_PORT         "SERVER_PORT"

/* �����ļ��ṹ */
struct CONFDeviceConfig{
	u16 flag;
	u16 port;    
    char APN[CONF_APN_LENGTH + 1];
	char address[CONF_ADDRESS_LENGTH + 1];
};

struct CONFDeviceConfig g_config;
static int g_configUpdated = BOOL_FALSE;

/* ȫ���ļ�ϵͳ */
static FATFS g_fs;

/* �����ļ� */
static FIL g_configFile;

static void _handleKeyValue(char* key, char* value)
{
    if (0 == strcmp(CONF_KEY_APN, key)){
        
        strncpy(g_config.APN, value, sizeof(g_config.APN));
        g_config.APN[sizeof(g_config.APN) - 1] = '\0';
        
    } else if (0 == strcmp(CONF_KEY_ADDRESS, key)) {

        strncpy(g_config.address, value, sizeof(g_config.address));
        g_config.address[sizeof(g_config.address) - 1] = '\0';    
		      
    } else if (0 == strcmp(CONF_KEY_PORT, key)) {
    
        g_config.port = atoi(value);
  
	}

    return;
}

static int _openAndRead(void)
{
   	FRESULT res;
    char buf[32];
    u32 readSize;

    /* �������ļ� */    
    res = f_open(&g_configFile, CONF_CONFIG_FILENAME, FA_READ);

    if (FR_OK != res){
        return ERROR_FAILED;
    }

    /* ��ȡ�ļ� */
    while(1){
        res = f_read(&g_configFile, buf, sizeof(buf), &readSize);

        if (FR_OK == res){
            CONF_ParserBuf(buf, readSize);
        } 

        if (FR_OK != res || readSize < sizeof(buf)){
            break;
        }
    }
    
    /* �ر��ļ� */
    f_close(&g_configFile);

    return ERROR_SUCCESS;
}

/* ���Դ������ļ����ɹ�����ERROR_SUCCESS��ʧ�ܷ���ERROR_FAILED */
static int _tryReadConfigFile(void)
{
	int ret = ERROR_FAILED;
	FRESULT res;
    
	/* ��������� */
	memset(&g_config, 0, sizeof(g_config));

	/* ���������ļ������� */
	CONF_SetHandler(_handleKeyValue);

	/* �����ļ�ϵͳ */
	res = f_mount(&g_fs, "", 1);    
	if (FR_OK == res){
	
		/* ���Դ򿪲���ȡ�ļ� */
		ret = _openAndRead();

		f_mount(NULL, "", 0);
	}
	
	return ret;
}

/* ��������Ƿ�Ϸ� */
static int _isConfigValid(struct CONFDeviceConfig* config)
{
	/* ���˿ڷ�Χ */
	if (0 == config->port) {
		return ERROR_FAILED;
	}

	/* ��ַ����Ϊ�� */
	if ('\0' == config->address[0]){
		return ERROR_FAILED;
	}

	return ERROR_SUCCESS;
}

/* �����ļ�ģ���ʼ��
TODO: �����Ż�ֱ��ʹ��flash����ʡ�ڴ�
 */
void CONF_InitConfig(void)
{
	int ret;

    /* �Ƚ����±������ΪFALSE */
    g_configUpdated = BOOL_FALSE;

	/* ���Զ�ȡsd���е������ļ� */
	ret = _tryReadConfigFile();

	/* ����ɹ���ȡ */
	if (ERROR_SUCCESS == ret){			

		printf("Read config APN[%s] address[%s] port[%hu]\r\n", 
				g_config.APN,
				g_config.address,
				g_config.port);

		/* ������úϷ��� */
		ret = _isConfigValid(&g_config);
		if (ERROR_SUCCESS == ret){

			/* �����ø���flash */
	        g_config.flag = CONF_CONFIG_FLAG;            
			FLASH_Write(&g_config, sizeof(g_config));

            /* ��������Ѿ����� */
            g_configUpdated = BOOL_TRUE;
			printf("Config is updated.\r\n");
		}
	}

    /* ���û�����ø��£����flash�лָ����� */
    if (BOOL_FALSE == g_configUpdated){
        
    	/* ��flash��ȡ���� */
    	FLASH_Read(&g_config, sizeof(g_config));

    	/* ������״������������ó�ʼ��Ϊ0 */
    	if (CONF_CONFIG_FLAG != g_config.flag){
    		memset(&g_config, 0, sizeof(g_config));
    	}
    }
    
	return;
}

/* �����Ƿ���� */
int CONF_IsUpdated(void)
{
	return g_configUpdated;
}

/* ��ȡ���� */
char* CONF_GetAddress(void)
{
	return g_config.address;
}

u16 CONF_GetPort(void)
{
	return g_config.port;
}

char* CONF_GetAPN(void)
{
	return g_config.APN;
}


