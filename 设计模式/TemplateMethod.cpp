/*
	Xwind工具
*/
#include <iostream>
using namespace std;

class MakeCar
{
public:
	virtual void MakeHead() = 0;
	virtual void MakeBody() = 0;
	virtual void MakeTail() = 0;
public:	
	//抽象类把业务逻辑做好
	void Make()
	{
		MakeHead();
		MakeBody();
		MakeTail();
	}
};
class Jeep:public MakeCar
{
public:
	virtual void MakeHead() 
	{
		cout<<"JeepHead"<<endl;
	}
	virtual void MakeBody()
	{
		cout<<"JeepBody"<<endl;
	}
	virtual void MakeTail()
	{
		cout<<"JeepTail"<<endl;
	}
};


void main()
{
	MakeCar* mc = new Jeep;
	mc->Make();

	delete mc;
	system("pause");
}
