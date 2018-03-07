#include <iostream>
using namespace std;
#include "string"

class Mediator;
class Person
{
public:
	virtual void getParter(Person *p) = 0;
	Person(string name, int sex, int condi, Mediator *m)
	{
		m_name = name;
		m_sex = sex;
		m_condi = condi;
		m_mediator = m;
	}
	string getName()
	{
		return m_name;
	}
	int getSex()
	{
		return m_sex;
	}
	int getCondi()
	{
		return m_condi;
	}
protected:
	string m_name;
	int m_sex;
	int m_condi;
	Mediator* m_mediator;
};
class Mediator
{
public:
	void getParter()
	{
		if (pWoman->getSex() == pMan->getSex())
		{
			cout<<"������ͬ����"<<endl;
			return;
		}
		if (pWoman->getCondi() == pMan->getCondi())
		{
			cout<<pWoman->getName()<<"��"<<pMan->getName()<<"����"<<endl;
		}
		else
		{
			cout<<pWoman->getName()<<"��"<<pMan->getName()<<"����"<<endl;
		}
	}
	void setMan(Person *person)
	{
		pMan = person;
	}
	void setWoman(Person *person)
	{
		pWoman = person;	
	}
private:
	Person *pMan;
	Person *pWoman;
};
class Woman:public Person
{
public:
	Woman(string name, int sex, int condi, Mediator *mediator):Person(name, sex, condi, mediator)
	{

	}
	virtual void getParter(Person *person)
	{
		m_mediator->setMan(person);
		m_mediator->setWoman(this);
		m_mediator->getParter();
	}
private:
	Person* person;
};
class Man:public Person
{
public:
	Man(string name, int sex, int condi, Mediator *mediator):Person(name, sex, condi, mediator)
	{

	}
	virtual void getParter(Person *person)
	{
		m_mediator->setMan(this);
		m_mediator->setWoman(person);
		m_mediator->getParter();
	}
private:
	Person* person;
};

void main()
{
	Mediator *m = new Mediator;
	Person* xs = new Woman("Сɺ", 2, 5, m);
	Person* xq = new Woman("Сǿ", 1, 5, m);
	m->setWoman(xs);
	m->setMan(xq);
	m->getParter();

	system("pause");
}