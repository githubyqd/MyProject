#ifndef _SOCKETCLIENT_H
#define _SOCKETCLIENT_H

#ifdef _cplusplus
extern "C"
#endif
/*
//��һ��
//socket�ͻ��˻�����ʼ��
int socketclient_init(void **handle);
//socket�ͻ��˱��ķ���
int socketclient_send(void *handle, unsigned char *buf, int buflen);
//socket�ͻ��˱��Ľ���
int socketclient_recv(void *handle, unsigned char *buf, int *buflen);
//socket�ͻ��˻����ͷ�
int socketclient_destory(void *handle);
*/
//�ڶ���
//socket�ͻ��˻�����ʼ��
int socketclient_init(void **handle);
//socket�ͻ��˱��ķ���
int socketclient_send(void *handle, unsigned char *buf, int buflen);
//socket�ͻ��˱��Ľ���
int socketclient_recv(void *handle, unsigned char **buf, int *buflen);
//socket�ͻ��˻����ͷ�
int socketclient_destory(unsigned char **buf);
#ifdef _cplusplus
}
#endif
#endif