#ifndef _SOCKETCLIENT_H
#define _SOCKETCLIENT_H

#ifdef _cplusplus
extern "C"
#endif
/*
//第一套
//socket客户端环境初始化
int socketclient_init(void **handle);
//socket客户端报文发送
int socketclient_send(void *handle, unsigned char *buf, int buflen);
//socket客户端报文接受
int socketclient_recv(void *handle, unsigned char *buf, int *buflen);
//socket客户端环境释放
int socketclient_destory(void *handle);
*/
//第二套
//socket客户端环境初始化
int socketclient_init(void **handle);
//socket客户端报文发送
int socketclient_send(void *handle, unsigned char *buf, int buflen);
//socket客户端报文接受
int socketclient_recv(void *handle, unsigned char **buf, int *buflen);
//socket客户端环境释放
int socketclient_destory(unsigned char **buf);
#ifdef _cplusplus
}
#endif
#endif