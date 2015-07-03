#ifndef _USART_IO_H_
#define _USART_IO_H_

#define USARTIO_FLAG_RXNE  0x20
#define USARTIO_FLAG_TXE   0x80

#define USARTIO_IsFlagSet(USART_ADDR, FLAG) (0 != (USART_ADDR->SR & FLAG))

/* �ӿڱ�¶���жϴ�����ʹ�� */
extern RingBuf g_Usart1ReadBufHead;
extern RingBuf g_Usart1WriteBufHead;
extern RingBuf g_Usart2ReadBufHead;
extern RingBuf g_Usart2WriteBufHead;
extern RingBuf g_Usart3ReadBufHead;
extern RingBuf g_Usart3WriteBufHead;

/* @brief ��ָ�����ڷ���һ���ַ�
* @param void* port           ָ���˿ڣ�����: USART1
* @param unsigned char ch   Ҫ���͵��ַ�
* @return �ɹ�����ERROR_SUCCESS,ʧ�ܷ���ERROR_FAILED
*/
int USARTIO_SendChar(void* port, unsigned char ch);

/* @brief ��ָ�����ڶ�ȡһ���ַ�
* @param void* port           ָ���˿ڣ�����: USART1
* @param unsigned char ch   Ҫ��ȡ���ַ�
* @return �ɹ�����ERROR_SUCCESS,ʧ�ܷ���ERROR_FAILED
*/
int USARTIO_RecvChar(void* port, unsigned char* ch);

/* ��ָ���˿ڷ���һ���ַ��� */
int USARTIO_SendString(void* port, unsigned char* str);

/* �򴮿ڷ��Ͷ��������� */
int USARTIO_SendData(void* port, unsigned char* data, int len);

/* ��ָ���˿ڽ���һ�� */
int USARTIO_ReadLine(void* port, unsigned char* buf, int bufsize);

void USARTIO_InitUsart1(void);
void USARTIO_InitUsart2(void);
void USARTIO_InitUsart3(void);

/* �жϻ����Ƿ�Ϊ�� */
int USARTIO_HaveLine(void *port);

#endif

