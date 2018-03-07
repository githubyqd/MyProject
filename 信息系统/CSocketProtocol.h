#pragma once
#include "iostream"
using namespace std;

class CSocketProtocol
{
public:	
	//客户端初始化
	virtual int cltSocketInit(/*out*/) = 0;
	//客户端发报文
	virtual int cltSocketSend(unsigned char *buf, int buflen) = 0;
	//客户端收报文
	virtual int cltSocketRev(unsigned char *buf, int *buflen) = 0;
	//客户端释放资源
	virtual int cltSocketDestory() = 0;
private:
	
};