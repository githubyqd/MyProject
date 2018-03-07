//Enegine Enegine4400cc	Enegine4500cc Car	WBM5 WBM6
#include <iostream>
using namespace std;

class Enegine
{
public:
	virtual void EnegineInstall() = 0;
};
class Enegine4400cc:public Enegine
{
public:
	virtual void EnegineInstall()
	{
		cout<<"����4400c����������װ���"<<endl;
	}
};
class Enegine4500cc:public Enegine
{
public:
	virtual void EnegineInstall()
	{
		cout<<"����4500c����������װ���"<<endl;
	}
};

class Car
{
public:
	Car(Enegine* energine)
	{
		m_energine = energine;
	}
	virtual void EnegineInstall() = 0;
protected:
	Enegine* m_energine;
};
class WBM5:public Car
{
public:
	WBM5(Enegine* energine):Car(energine)
	{
		m_energine = energine;
	}
	virtual void EnegineInstall() 
	{
		cout<<"����������"<<endl;
		m_energine->EnegineInstall();
	}
};

void main()
{
	Enegine* myenergine = new Enegine4500cc;
	Car *mycar = new WBM5(myenergine);
	mycar->EnegineInstall();

	delete mycar;
	system("pause");
}
