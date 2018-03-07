/*代理模式（Proxy）						
提供一种代理控制这个对象的访问
代理是具有与代理元（被代理的对象）具有相同的接口的类
客户端必须通过代理与被代理的目标类交互*/

#include <iostream>
using namespace std;
class BookStore
{
public:
	virtual void SaleBook()
	{
		cout<<"SaleBook卖书"<<endl;
	}
};
class RealBookStore:public BookStore
{
public:
	virtual void  SaleBook()
	{
		cout<<"RealBookStore卖书"<<endl;
	}
};
class DangProxy:public RealBookStore
{
public:
	virtual void  SaleBook()
	{
		cout<<"DangProxy卖书"<<endl;

		RealBookStore realbookstore;
		realbookstore.SaleBook();
		doubleEleven();
		doubleEleven();
		doubleEleven();
	}
	void doubleEleven()
	{
		cout<<"活动促销"<<endl;
	}
};

void main()
{
	DangProxy *d1 = new DangProxy;
	d1->SaleBook();
	system("pause");
}