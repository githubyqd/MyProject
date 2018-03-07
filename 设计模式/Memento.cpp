#include <iostream>
using namespace std;
#include "string"

class Memento
{
public:
	Memento(string name, int age)
	{
		m_name = name;
		m_age = age;
	}
	string getName()
	{
		return m_name;
	}
	int getage()
	{
		return m_age;
	}
private:
	string m_name;
	int m_age;
};
class Person
{
public:
	Person(string name, int age)
	{
		m_name = name;
		m_age = age;
	}
	string getName()
	{
		return m_name;
	}
	int getage()
	{
		return m_age;
	}
	void Print()
	{
		cout<<"m_name:"<<m_name<<", m_age:"<<m_age<<endl;
	}
	//保存
	Memento* CreateMemento()
	{
		return new Memento(m_name, m_age);
	}
	//还原
	void ReMemento(Memento* memento)
	{
		m_name = memento->getName();
		m_age = memento->getage();
	}
private:
	string m_name;
	int m_age;
};

void main()
{
	Person *p1 = new Person("张三", 58);
	Memento *memento = p1->CreateMemento();
	p1->ReMemento(memento);
	p1->Print();

	system("pause");
}