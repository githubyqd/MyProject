/*װ����ģʽ��Decorator��					
��̬�ĸ�������Ӷ����ְ�𣨳������ܿ����Σ�*/

#include <iostream>
using namespace std;

class Car
{
public:
	virtual void show() = 0;
};
class RunCar:public Car
{
public:
	virtual void show()
	{
		cout<<"������"<<endl;
	}
};
class SwimCarDecorator:public Car
{
public:
	SwimCarDecorator(Car *car)
	{
		m_car = car;
	}
	virtual void show()
	{
		m_car->show();
		cout<<"������"<<endl;
	}
private:
	Car* m_car;
};


void main()
{
	Car* rcar = new RunCar;
	rcar->show();

	SwimCarDecorator* scar = new SwimCarDecorator(rcar);
	scar->show();
	system("pause");
}
