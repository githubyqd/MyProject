#include <iostream>
using namespace std;
#include "list"

class Doctor
{
public:
	void TeatEye()
	{
		cout<<"看眼科"<<endl;
	}
	void TeatNose()
	{
		cout<<"看鼻科"<<endl;
	}
};

//行为命令
class Command
{
public:
	virtual void Treat() = 0;
};
class CommandTeatEye:public Command
{
public:
	CommandTeatEye(Doctor* doctor)
	{
		m_doctor = doctor;
	}
	virtual void Treat()
	{
		m_doctor->TeatEye();
	}
private:
	Doctor* m_doctor;
};
class CommandTeatNose:public Command
{
public:
	CommandTeatNose(Doctor* doctor)
	{
		m_doctor = doctor;
	}
	virtual void Treat()
	{
		m_doctor->TeatNose();
	}
private:
	Doctor* m_doctor;
};

class BeautyNurse
{
public:
	BeautyNurse(Command* command)
	{
		m_command = command;
	}
	void SubTreatCase()
	{
		m_command->Treat();
	}
private:
	Command* m_command;
};
class AdvNurse
{
public:
	AdvNurse()
	{
		m_list.clear();
	}
	void SetCommand(Command* command)
	{
		m_list.push_back(command);
	}
	void SubmittedCase()
	{
		for (list<Command*>::iterator it=m_list.begin(); it!=m_list.end(); it++)
		{
			(*it)->Treat();
		}
	}
private:
	list<Command*> m_list;
};

void main()
{
	Doctor* d = new Doctor;
	Command* ce = new CommandTeatEye(d);
	Command* cn = new CommandTeatNose(d);
	AdvNurse* advn = new AdvNurse;
	advn->SetCommand(ce);
	advn->SetCommand(cn);
	advn->SubmittedCase();

	delete advn;
	delete cn;
	delete ce;
	delete d;
	system("pause");
}