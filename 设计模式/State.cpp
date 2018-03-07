#include <iostream>
using namespace std;

class Worker;
class State
{
public:
	virtual void DoThings(Worker* worke) = 0;
};
class State1:public State
{
public:
	virtual void DoThings(Worker* worke);
};
class State2:public State
{
public:
	virtual void DoThings(Worker* worke);
};

class Worker
{
public:
	Worker()
	{
		m_curstate = new State1;
	}
	void setHour(int hour)
	{
		m_hour = hour;
	}
	int getHour()
	{
		return m_hour;
	}

	void setCurstate(State *state)
	{
		m_curstate = state;
	}
	State* getCurstate()
	{
		return m_curstate;
	}

	void DoThings()
	{
		m_curstate->DoThings(this);
	}
private:
	int m_hour;
	State *m_curstate;
};

void State1::DoThings(Worker* worke)
{
	if (worke->getHour() == 7 || worke->getHour() == 8)
	{
		cout<<"³ÔÔç·¹"<<endl;
	}
	else
	{
		delete worke->getCurstate();
		worke->setCurstate(new State2);
		worke->getCurstate()->DoThings(worke);
	}
}
void State2::DoThings(Worker* worke)
{
	if (worke->getHour() == 9 || worke->getHour() == 10)
	{
		cout<<"¹¤×÷"<<endl;
	}
	else
	{
		delete worke->getCurstate();
		worke->setCurstate(new State1);
		worke->getCurstate()->DoThings(worke);
	}
}

void main()
{
	Worker* woker = new Worker;
	woker->setHour(7);
	woker->DoThings();

	woker->setHour(9);
	woker->DoThings();

	delete woker;
	system("pause");
}