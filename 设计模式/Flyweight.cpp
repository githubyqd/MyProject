#include <iostream>
using namespace std;
#include"string"
#include"map"

class Person
{
public:
	Person(string name, int age)
	{
		m_name = name;
		m_age = age;
	}
	virtual void Print()= 0;
protected:
	string m_name;
	int m_age;
};
class Teacher:public Person
{
public:
	Teacher(string name, int age, string id):Person(name, age)
	{
		m_id = id;
	}
	virtual void Print()
	{
		cout<<"m_name:"<<m_name<<", m_age:"<<m_age<<", m_id:"<<m_id<<endl;
	}
private:
	string m_id;
};
class FlyweightTeacherFactory
{
public:
	FlyweightTeacherFactory()
	{
		map1.clear();
	}
	~FlyweightTeacherFactory()
	{
		while (!map1.empty())
		{
			map<string, Teacher*>::iterator it = map1.begin();
			map1.erase(it);
			delete it->second;
		}
	}
	Person* AddTeacher(string id)
	{
		map<string, Teacher*>::iterator it = map1.find(id);
		Teacher* temp = NULL;
		if(it == map1.end())
		{
			string tempname;
			int tenmage;
			cout<<"请输入姓名：";
			cin>>tempname;
			cout<<"\n请输入年龄：";
			cin>>tenmage;

			temp = new Teacher(tempname, tenmage, id);
			map1.insert(pair<string, Teacher*>(id, temp));
		}
		else
		{
			temp = it->second;
		}
		return temp;
	}
private:
	map<string, Teacher*> map1;
};

void main()
{
	Person *p1 = NULL;
	Person *p2 = NULL;
	FlyweightTeacherFactory *fwtf = new FlyweightTeacherFactory;
	p1 = fwtf->AddTeacher("001");
	p1->Print();
	p2 = fwtf->AddTeacher("001");
	p2->Print();

	delete p1, p2;
	system("pause");
}
