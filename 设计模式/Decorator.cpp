/*装饰着模式（Decorator）					
动态的给对象添加额外的职责（车可以跑可以游）*/

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
		cout<<"可以跑"<<endl;
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
		cout<<"可以游"<<endl;
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
