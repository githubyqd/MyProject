#include "CSocketProtocol.h"

class CSckFactoryImp1:public CSocketProtocol
{
public:
	//�ͻ��˳�ʼ��
	virtual int cltSocketInit();
	//�ͻ��˷�����
	virtual int cltSocketSend(unsigned char *buf, int buflen);
	//�ͻ����ձ���
	virtual int cltSocketRev(unsigned char *buf, int *buflen);
	//�ͻ����ͷ���Դ
	virtual int cltSocketDestory();
private:
	unsigned char *p;
	int len;
};