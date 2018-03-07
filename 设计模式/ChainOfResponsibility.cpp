#include <iostream>
using namespace std;

class CarHandle
{
public:
	virtual void HandleCar() = 0;
	CarHandle* SetHandleCar(CarHandle* handlecar)
	{
		m_handlecar = handlecar;
		return m_handlecar;
	}
protected:
	CarHandle* m_handlecar;
};
class HeadHandle:public CarHandle
{
public:
	virtual void HandleCar() 
	{
		cout<<"�쳵ͷ"<<endl;
		if (m_handlecar != NULL)//��һ������ʼ
		{
			m_handlecar->HandleCar();
		}
	}
};
class BodyHandle:public CarHandle
{
public:
	virtual void HandleCar() 
	{
		cout<<"�쳵��"<<endl;
		if (m_handlecar != NULL)
		{
			m_handlecar->HandleCar();
		}
	}
};
class TailHandle:public CarHandle
{
public:
	virtual void HandleCar() 
	{
		cout<<"�쳵β"<<endl;
		if (m_handlecar != NULL)
		{
			m_handlecar->HandleCar();
		}
	}
};

void main()
{
	CarHandle *hh = new HeadHandle;
	CarHandle *bh = new BodyHandle;
	CarHandle *th = new TailHandle;
	hh->SetHandleCar(bh);
	bh->SetHandleCar(th);
	th->SetHandleCar(NULL);

	hh->HandleCar();

	delete hh;
	delete bh;
	delete th;
	system("pause");
}