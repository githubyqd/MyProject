#include "CSocketProtocol.h"

class CSckFactoryImp1:public CSocketProtocol
{
public:
	//客户端初始化
	virtual int cltSocketInit();
	//客户端发报文
	virtual int cltSocketSend(unsigned char *buf, int buflen);
	//客户端收报文
	virtual int cltSocketRev(unsigned char *buf, int *buflen);
	//客户端释放资源
	virtual int cltSocketDestory();
private:
	unsigned char *p;
	int len;
};