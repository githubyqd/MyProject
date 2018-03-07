#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SCK_HANDLE
{
	char version[64];//�汾��ip���˿�
	char ip[128];
	int port;

	unsigned char *p;
	int plen;
}SCK_HANDLE;//��̬���ڲ��������ͣ��������ͷ�װ

//socket�ͻ��˻�����ʼ��
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
	*handle = hdl;//��Ӹ�ֵ
	printf("Func socketclient_init() End\n");
	return ret;
}
//socket�ͻ��˱��ķ���
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
//socket�ͻ��˱��Ľ���
_declspec(dllexport)
//int socketclient_recv(void *handle, unsigned char *buf, int *buflen)
int socketclient_recv(void *handle, unsigned char **buf, int *buflen)//�ڶ���api
{
	int ret = 0;
	SCK_HANDLE *hdl = NULL;
	unsigned char *temp = NULL;//�ڶ���api
	if(handle == NULL|| buf == NULL|| buflen == NULL)
	{
		ret = -1;
		printf("func socketclient_recv() err:%d\n", ret);
		return ret;
	}
	hdl = (SCK_HANDLE*)handle;
	temp = (unsigned char*)malloc(hdl->plen);//�ڶ���api
	if (temp == NULL)
	{
		ret = -2;
		printf("func socketclient_recv2() err:%d\n", ret);
		return ret;
	}
	//memcpy(buf, hdl->p, hdl->plen);
	memcpy(temp, hdl->p, hdl->plen);//�ڶ���api
	*buflen = hdl->plen;

	*buf =temp;//�ڶ���api
	return ret;
}
//socket�ͻ��˻����ͷ�
_declspec(dllexport)
//int socketclient_destory(void *handle)
int socketclient_destory(unsigned char **buf)//�ڶ���api
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
