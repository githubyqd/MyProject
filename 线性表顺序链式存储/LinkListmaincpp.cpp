#include <iostream>
using namespace std;
#include "linklist.cpp"
struct Teacher{
public:
	char name[64];
	int age;
	char* pdes;  
	Teacher()
	{
		memset(name, 0, sizeof(name));
		age = 0;
		pdes = NULL;
	}
	~Teacher()
	{
		if(pdes != NULL)
		{
			free(pdes);
		}
	}
	Teacher(Teacher &obj)
	{
		pdes = (char*)malloc(100);
		strcpy(this->name, obj.name);
		strcpy(this->pdes, obj.pdes);
		this->age = obj.age;}
		Teacher& operator=(Teacher &obj)
		{
			if(pdes!=NULL)
			{
				free(pdes);
				pdes = NULL;
			}
			if(pdes==obj.pdes)//t1 = t1
			{
				free(pdes);
				pdes = NULL;
				return *this;
			}
			pdes = (char*)malloc(100);
			strcpy(this->name, obj.name);
			strcpy(this->pdes, obj.pdes);
			this->age = obj.age;
			return *this;
		}
	}
};

void main()
{
	Teacher t1, t2, t3;
	Teacher* temp = NULL;
	t1.age = 31;t2.age = 32; t3.age = 33;
	Teacher *p1, *p2, *p3;
	p1 = &t1; p2 = &t2; p3 = &t3;
	LinkList<Teacher*> list;
	list.LinkList_Insert(p1, 0);
	list.LinkList_Insert(p2, 0);
	list.LinkList_Insert(p3, 0);
	for(int i = 0; i<list.LinkList_Length(); i++)
	{
		list.LinkList_Get(i, temp);
		out<<temp->age<<" ";
	}
	list.LinkList_Clear();
	system("pause");
}
