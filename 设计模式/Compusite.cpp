#include <iostream>
using namespace std;
#include"list"
#include"string"

class IFile
{
public:
	virtual void display() = 0;
	virtual int add(IFile* ifile) = 0;
	virtual int remove(IFile* ifile) = 0;
	virtual list<IFile*>* getchild() = 0;
};
//文件结点
class File:public IFile
{
public:
	File(string name)
	{
		m_name = name;
	}
	virtual void display()
	{
		cout<<m_name<<endl;
	}
	virtual int add(IFile* ifile)
	{
		return -1;
	}
	virtual int remove(IFile* ifile)
	{
		return -1;
	}
	virtual list<IFile*>* getchild() 
	{
		return NULL;
	}
private:
	string m_name;
};
//目录结点
class Dir:public IFile
{
public:
	Dir(string name)
	{
		m_name = name;
		m_list = new list<IFile*>;
		m_list->empty();
	}
	virtual void display()
	{
		cout<<m_name<<endl;
	}
	virtual int add(IFile* ifile)
	{
		m_list->push_back(ifile);
		return 0;
	}
	virtual int remove(IFile* ifile)
	{
		m_list->remove(ifile);
		return 0;
	}
	virtual list<IFile*>* getchild() 
	{
		return m_list;
	}
private:
	string m_name;
	list<IFile*> *m_list;
};

void showTree(Dir *root,int lev)
{
	if(root == NULL)
	{
		return;
	}
	for(int i=0; i<lev; i++)
	{
		cout<<"\t";
	}
	root->display();
	list<IFile*> *mylist = root->getchild(); 
	if(mylist != NULL)
	{
		for (list<IFile*>::iterator it=mylist->begin(); it!=mylist->end(); it++)
		{
			if((*it)->getchild() == NULL)
			{
				for(int i=0; i<=lev; i++)
				{
					cout<<"\t";
				}
				(*it)->display();
			}
			else
			{
				showTree((Dir*)*it, lev+1);
			}
		}
	}
}

void main()
{
	Dir *root = new Dir("C");
	Dir* dir1 = new Dir("111dir");
	File* file1 = new File("aaa.txt");
	list<IFile*> *mylist = root->getchild();
	root->add(dir1);
	root->add(file1);

	Dir* dir2 = new Dir("222dir");
	File* file2 = new File("bbb.txt");
	dir1->add(dir2);
	dir1->add(file2);
	showTree(root, 0);

	system("pause");
}
	