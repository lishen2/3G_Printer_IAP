#ifndef _CONF_PARSER_H_
#define _CONF_PARSER_H_

/* ���ڴ����ֵ�ԵĻص� */
typedef void (*CONF_HDL_CB)(char* key, char* value);

/* ���ô����ֵ�ԵĻص����� */
void CONF_SetHandler(CONF_HDL_CB cb);

/* ���������� */
void CONF_ParserBuf(char* buf, int size);

#endif

