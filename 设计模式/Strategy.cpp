#include <iostream>
using namespace std;

class Strcategy
{
public:
	virtual void crypt() = 0;
};
//�ԳƼ���	������Կ�ͽ�����Կһ�����ٶȿ죬���ܴ���ļ�
//�ǶԳƼ���	������Կ�ͽ�����Կ��һ������Կ��˽Կ�����ٶ�����ȫ
class AES:public Strcategy
{
public:
	virtual void crypt()
	{
		cout<<"AES�����㷨"<<endl;
	}
};
class DES:public Strcategy
{
public:
	virtual void crypt()
	{
		cout<<"DES�����㷨"<<endl;
	}
};

class Context
{
public:
	void setStrcategy(Strcategy* strcategy)
	{
		m_strcategy = strcategy;
	}
	void Operator()
	{
		m_strcategy->crypt();
	}
private:
	Strcategy* m_strcategy;
};

void main()
{
	Context* context = new Context;
	Strcategy* strcategy = new AES;
	context->setStrcategy(strcategy);
	context->Operator();

	delete context;
	system("pause");
}