#ifndef __UTILS_H
#define __UTILS_H

#define ERROR_TIMEOUT -2
#define ERROR_ERROR -1
#define ERROR_FAILED ERROR_ERROR
#define ERROR_SUCCESS 0

#define BOOL_TRUE  1
#define BOOL_FALSE 0

#define HZ   100

#define inline __inline

//�ж�a�Ƿ���b֮��
#define time_after(a, b) ((signed int)((signed int)(b) - (signed int)(a)) < 0)

/* ��ʱʹ�õļ����� */
extern vu32 g_jiffies;

/* ���ַ�ת��Ϊ���Ӧ�����֣����Դ���16���ƺʹ�Сд */
static inline unsigned char UTILS_Char2Num(char ch){
	
	if (ch >= 48 && ch <= 57){
		return ch - 48;
	} else if (ch >= 65 && ch <= 70){
		return ch - 55;
	}  else if (ch >= 97 && ch <= 102){
		return ch - 87;
	} else {
		return 0;
	}
}

/* ������ת��Ϊ���Ӧ���ַ���ת�����Ϊ16���� */
static inline unsigned char UTILS_Num2Char(unsigned char num){
    if (num < 10){
        return num + '0';
    } else if (num >= 10 && num < 16){
        return num - 10 + 'A';
    } else {
        return 0;
    }
}

/* ��������ʾһ��16�������ֵ���ĸת��Ϊ16������ */
static inline unsigned char UTILS_ASCII2Bin(char high, 
                                            char low)
{
	high = UTILS_Char2Num(high);
	low = UTILS_Char2Num(low);

	return (high << 4) | low;
}

/* ������ʱ */
void delay_ms(int n);

void HW_InitSysTick(void);

void HW_CommonInit(void);

/* ��ȡ�豸ID */
char* UTILS_GetDeviceID(void);

/* ��ȡ�����汾�� */
const char* UTILS_GetVersion(void);

/* ����������ת��ΪASCII */
void UTILS_ConvByteToASCII(char* inbuf, int inbufsize, char* outbuf, int outbufsize);


#endif /* __UITLS_H */
