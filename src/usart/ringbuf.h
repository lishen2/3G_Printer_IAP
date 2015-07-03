#ifndef _RANGBUF_H_
#define _RANGBUF_H_

typedef struct RingBuf{
	volatile int readpos;
	volatile int writepos;	
	unsigned int size;   //�����С������
    unsigned char* data;
    volatile int lines;  //��ǻ������е�����    
}RingBuf;

/* �жϻ������Ƿ�Ϊ�� */
#define RINGBUF_ISEMPTY(buf) ((buf)->readpos == (buf)->writepos)

/* �жϻ��������Ƿ���������һ�� */
#define RINGBUF_HAVELINE(buf) ((buf)->lines > 0)

/* ���ú�ȡ�������б�� */
#define RINGBUF_INCLINE(buf) (++((buf)->lines))
#define RINGBUF_DECLINE(buf) (--((buf)->lines))

/* init rangbuffe structer, with byte array and array size */
void Ringbuf_Init(RingBuf *buf, unsigned char* databuf, int bufsize);

/* put one char into buf, 
 * return ERROR_SUCCESS on success, 
 * otherwise return ERROR_FAILED
 * */
int Ringbuf_PutChar(RingBuf *buf, unsigned char ch);

/* put one char into buf, 
 * return one char on success, 
 * otherwise return error code which is less then zero
 * */
int Ringbuf_GetChar(RingBuf *buf);

#endif

