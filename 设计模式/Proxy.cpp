/*����ģʽ��Proxy��						
�ṩһ�ִ�������������ķ���
�����Ǿ��������Ԫ��������Ķ��󣩾�����ͬ�Ľӿڵ���
�ͻ��˱���ͨ�������뱻�����Ŀ���ཻ��*/

#include <iostream>
using namespace std;
class BookStore
{
public:
	virtual void SaleBook()
	{
		cout<<"SaleBook����"<<endl;
	}
};
class RealBookStore:public BookStore
{
public:
	virtual void  SaleBook()
	{
		cout<<"RealBookStore����"<<endl;
	}
};
class DangProxy:public RealBookStore
{
public:
	virtual void  SaleBook()
	{
		cout<<"DangProxy����"<<endl;

		RealBookStore realbookstore;
		realbookstore.SaleBook();
		doubleEleven();
		doubleEleven();
		doubleEleven();
	}
	void doubleEleven()
	{
		cout<<"�����"<<endl;
	}
};

void main()
{
	DangProxy *d1 = new DangProxy;
	d1->SaleBook();
	system("pause");
}