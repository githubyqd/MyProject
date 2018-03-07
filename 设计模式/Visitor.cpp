#include <iostream>
using namespace std;
#include"list"

class ParkElement;
class Visitor
{
public:
	virtual void visit(ParkElement *parkelement) = 0;
};
class VisiteA:public Visitor
{
public:
	virtual void visit(ParkElement *parkelement)
	{
		cout<<"完成公园A打扫"<<endl;
	}
};
class VisiteB:public Visitor
{
public:
	virtual void visit(ParkElement *parkelement)
	{
		cout<<"完成公园B打扫"<<endl;
	}
};
class ManagerVisitor:public Visitor
{
public:
	virtual void visit(ParkElement *parkelement)
	{
		cout<<"管理者访问公园各个部分"<<endl;
	}
};
class ParkElement
{
public:
	virtual void accept(Visitor *visitor) = 0;
};
class ParkA:public ParkElement
{
public:
	virtual void accept(Visitor *visitor)
	{
		visitor->visit(this);
	}
};
class ParkB:public ParkElement
{
public:
	virtual void accept(Visitor *visitor)
	{
		visitor->visit(this);
	}
};
//整个公园
class Park:public ParkElement
{
public:
	Park()
	{
		m_list.clear();
	}
	void SetParkElement(ParkElement* pe)
	{
		m_list.push_back(pe);
	}
	virtual void accept(Visitor *visitor)
	{
		for (list<ParkElement*>::iterator it=m_list.begin(); it!=m_list.end(); it++)
		{
			(*it)->accept(visitor);
		}
	}
private:
	list<ParkElement*> m_list;
};

void main()
{
	Visitor* vmanager = new ManagerVisitor;
	Park* park = new Park;
	ParkElement *pa = new ParkA;
	ParkElement *pb = new ParkB;

	park->SetParkElement(pa);
	park->SetParkElement(pb);
	park->accept(vmanager);
	delete pb;
	delete pa;
	delete park;
	delete vmanager;
	
	system("pause");
}