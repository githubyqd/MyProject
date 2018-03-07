#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socketclient.h"

int main()
{
	int ret = 0;
	void *handle = NULL;
	unsigned char buf[128];
	int buflen = 3;
	//unsigned char outbuf[128];/*in*/ //常量指针第一套api函数
	//int outbuflen = 3;//第一套api函数
	unsigned char *pout = NULL;
	int poutlen = 0;
	memcpy(buf, "ssfddsss", buflen);
	ret = socketclient_init(&handle);
	if(ret != 0)
	{
		printf("func socketclient_init() err:%d\n", ret);
		return ret;
	}
	ret = socketclient_send(handle, buf, buflen);
	if(ret != 0)
	{
		printf("func socketclient_send() err:%d\n", ret);
		return ret;
	}
	//ret = socketclient_recv(handle, outbuf, &outbuflen);//第一套api函数
	ret = socketclient_recv(handle, &pout, &poutlen);
	if(ret != 0)
	{
		printf("func socketclient_recv() err:%d\n", ret);
		return ret;
	}
	//ret = socketclient_destory(handle);//第一套api函数
	ret = socketclient_destory(&pout);
	if(ret != 0)
	{
		printf("func socketclient_destory() err:%d\n", ret);
		return ret;
	}

	system("pause");
}