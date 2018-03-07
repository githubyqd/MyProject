#include <iostream>
using namespace std;
#include "list"
#include "string"

class Secretary;
//观察者
class ObserverPlayer
{
public:
	ObserverPlayer(Secretary *secretary)
	{
		m_secretary = secretary;
	}
	void update(string action)
	{
		cout<<action<<endl;
	}
private:
	Secretary* m_secretary;
};

class Secretary
{
public:
	Secretary()
	{
		m_list.clear();
	}
	void setObserverPlayer(ObserverPlayer* o)
	{
		m_list.push_back(o);
	}
	void Notify(string info)
	{
		for (list<ObserverPlayer*>::iterator it=m_list.begin(); it!=m_list.end(); it++)
		{
			(*it)->update(info);
		}
	}
private:
	list<ObserverPlayer*> m_list;
};


void main()
{
	Secretary *s = new Secretary;
	ObserverPlayer *o1 = new ObserverPlayer(s);
	ObserverPlayer *o2 = new ObserverPlayer(s);
	s->setObserverPlayer(o1);
	s->setObserverPlayer(o2);
	s->Notify("老板来了");
	s->Notify("老板走了");
	
	system("pause");
}