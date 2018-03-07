#include <iostream>
using namespace std;

class SubSystem1
{
public:
	void dothing()
	{
		cout<<"我是子系统1"<<endl;
	}
};
class SubSystem2
{
public:
	void dothing()
	{
		cout<<"我是子系统2"<<endl;
	}
};
class SubSystem3
{
public:
	void dothing()
	{
		cout<<"我是子系统3"<<endl;
	}
};
class Facade
{
public:
	Facade()
	{
		 sy1 =new SubSystem1;
		 sy2 =new SubSystem2;
		 sy3 =new SubSystem3;
	}
	void dothing()
	{
		sy1->dothing();
		sy2->dothing();
		sy3->dothing();
	}
private:
	SubSystem1* sy1;
	SubSystem2* sy2;
	SubSystem3* sy3;
};

void main()
{
	Facade* facade = new Facade;
	facade->dothing();

	delete facade;
	system("pause");
}
