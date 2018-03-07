/*原型模式（Protofype）					
用原型实例指定创建对象的种类，一个复杂对象具有自我复制功能，统一一套接口*/

#include <iostream>
using namespace std;
#include"string"

class Person
{
public:
	virtual void Print() = 0;
	virtual Person* Clone() = 0; 
};
class CPlusProgramer:public Person
{
public:
	CPlusProgramer()
	{
		m_name = "";
		m_age = 0;
		Setm_resum("aaa");
	}
	CPlusProgramer(string name, int age)
	{
		m_name = name;
		m_age = age;
		Setm_resum("aaa");
	}
	void Setm_resum(char* p)
	{
		if (m_resum == NULL)
		{
			delete m_resum;
		}
		m_resum =new char[strlen(p)+1];
		strcpy(m_resum, p);
	}
	virtual Person* Clone() 
	{
		CPlusProgramer* temp = new CPlusProgramer;
		temp->m_resum = new char[strlen(this->m_resum)+1];
		strcpy(temp->m_resum, m_resum);
		*temp = *this;
		return temp;
	}
	virtual void Print()
	{
		cout<<"m_name"<<m_name<<" m_age"<<m_age<<m_resum<<endl;
	}
private:
	string m_name;
	int m_age;
	char* m_resum;
};

void main()
{
	Person* person = new CPlusProgramer("张三", 54);
	person->Print();

	Person* person1 = person->Clone();
	person1->Print();
	system("pause");
}