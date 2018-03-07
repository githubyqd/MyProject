#include <iostream>
using namespace std;

class Current18v
{
public:
	virtual void us18vCurrent()
	{
		cout<<"ʹ��18v������"<<endl;
	};
};
class Current220v
{
public:
	void us220vCurrent()
	{
		cout<<"ʹ��220v������"<<endl;
	};
};
class Adapter:public Current18v
{
public:
	Adapter(Current220v* p220v)
	{
		m_p220v = p220v;
	}
	virtual void us18vCurrent()
	{
		cout<<"Adaptorʹ��"<<endl;
		m_p220v->us220vCurrent();
	}
private:
	Current220v* m_p220v;
};

void main()
{
	Current220v *p220v = new Current220v;
	Adapter* myadaptor = new Adapter(p220v);
	myadaptor->us18vCurrent();

	delete p220v;
	delete myadaptor;
	system("pause");
}
