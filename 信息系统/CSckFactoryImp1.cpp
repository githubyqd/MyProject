#pragma once
#include "iostream"
using namespace std;
#include "CSckFactoryImp1.h"


//客户端初始化
int CSckFactoryImp1::cltSocketInit()
{
	p = NULL ;
	len = 0;
	return 0;
}
//客户端发报文
int CSckFactoryImp1::cltSocketSend(unsigned char *buf, int buflen)
{
	p = new unsigned char[buflen + 1];
	memcpy(p, buf, buflen);
	if (p == NULL)
	{
		return -1;
	}
	len = buflen;
	return 0;
}
//客户端收报文
int CSckFactoryImp1::cltSocketRev(unsigned char *buf, int *buflen)
{
	if (buf == NULL || buflen == 0)
	{
		return -1;
	}
	len = *buflen;
	p = new unsigned char[*buflen+1];
	return 0;
}
//客户端释放资源
int CSckFactoryImp1::cltSocketDestory()
{
	if (p != NULL)
	{
		delete []p;
		p = NULL;
		len = 0;
	}
	return 0;
}

	
