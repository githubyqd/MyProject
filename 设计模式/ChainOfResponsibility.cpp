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
		cout<<"造车头"<<endl;
		if (m_handlecar != NULL)//下一个任务开始
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
		cout<<"造车身"<<endl;
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
		cout<<"造车尾"<<endl;
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