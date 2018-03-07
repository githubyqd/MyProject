#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SCK_HANDLE
{
	char version[64];//版本、ip、端口
	char ip[128];
	int port;

	unsigned char *p;
	int plen;
}SCK_HANDLE;//动态库内部数据类型，数据类型封装

//socket客户端环境初始化
_declspec(dllexport)
int socketclient_init(void **handle)
{
	int ret = 0;
	SCK_HANDLE *hdl = NULL;
	printf("Func socketclient_init() begain\n");
	hdl = (SCK_HANDLE*)malloc(sizeof(SCK_HANDLE));
	if(hdl == NULL)
	{
		ret = -1;
		printf("func socketclient_init() err:%d\n", ret);
		return ret;
	}
	memset(hdl, 0, sizeof(SCK_HANDLE));
	strcpy(hdl->ip, "192.168.6.264");
	hdl->port = 8081;
	*handle = hdl;//间接赋值
	printf("Func socketclient_init() End\n");
	return ret;
}
//socket客户端报文发送
_declspec(dllexport)
int socketclient_send(void *handle, unsigned char *buf, int buflen)
{
	int ret = 0;
	SCK_HANDLE *hdl = NULL;
	hdl = (SCK_HANDLE*)handle;
	hdl->p = (unsigned char*)malloc(buflen*sizeof(unsigned char));
	if(hdl->p == NULL)
	{
		ret = -1;
		printf("func socketclient_send() err:%d\n", ret);
		return ret;
	}
	memcpy(hdl->p, buf, buflen);
	hdl->plen = buflen;
	return ret;
}
//socket客户端报文接受
_declspec(dllexport)
//int socketclient_recv(void *handle, unsigned char *buf, int *buflen)
int socketclient_recv(void *handle, unsigned char **buf, int *buflen)//第二套api
{
	int ret = 0;
	SCK_HANDLE *hdl = NULL;
	unsigned char *temp = NULL;//第二套api
	if(handle == NULL|| buf == NULL|| buflen == NULL)
	{
		ret = -1;
		printf("func socketclient_recv() err:%d\n", ret);
		return ret;
	}
	hdl = (SCK_HANDLE*)handle;
	temp = (unsigned char*)malloc(hdl->plen);//第二套api
	if (temp == NULL)
	{
		ret = -2;
		printf("func socketclient_recv2() err:%d\n", ret);
		return ret;
	}
	//memcpy(buf, hdl->p, hdl->plen);
	memcpy(temp, hdl->p, hdl->plen);//第二套api
	*buflen = hdl->plen;

	*buf =temp;//第二套api
	return ret;
}
//socket客户端环境释放
_declspec(dllexport)
//int socketclient_destory(void *handle)
int socketclient_destory(unsigned char **buf)//第二套api
{
	int ret = 0;
	if(buf == NULL)
	{
		ret = -1;
		printf("func socketclient_destory() err:%d\n", ret);
		return ret;
	}
	if(buf!=NULL)
	{
		free(*buf);
	}
	*buf = NULL;	
	return ret;
}
