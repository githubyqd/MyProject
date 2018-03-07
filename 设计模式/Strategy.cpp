#include <iostream>
using namespace std;

class Strcategy
{
public:
	virtual void crypt() = 0;
};
//对称加密	加密密钥和解密密钥一样，速度快，加密大块文件
//非对称加密	加密密钥和解密密钥不一样（公钥和私钥），速度慢安全
class AES:public Strcategy
{
public:
	virtual void crypt()
	{
		cout<<"AES加密算法"<<endl;
	}
};
class DES:public Strcategy
{
public:
	virtual void crypt()
	{
		cout<<"DES加密算法"<<endl;
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