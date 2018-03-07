#pragma once
#include "iostream"
using namespace std;

class CSocketProtocol
{
public:	
	//�ͻ��˳�ʼ��
	virtual int cltSocketInit(/*out*/) = 0;
	//�ͻ��˷�����
	virtual int cltSocketSend(unsigned char *buf, int buflen) = 0;
	//�ͻ����ձ���
	virtual int cltSocketRev(unsigned char *buf, int *buflen) = 0;
	//�ͻ����ͷ���Դ
	virtual int cltSocketDestory() = 0;
private:
	
};