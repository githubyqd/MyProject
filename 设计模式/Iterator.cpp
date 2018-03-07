#include <iostream>
using namespace std;

typedef int Object;
#define SIZE 5

class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual Object CurrentItem() = 0;
};

class Aggregate
{
public:
	virtual Iterator* CreateIterator() = 0;
	virtual Object getItem(int index) = 0;
	virtual int getSize() = 0;
};

class ConcreteIterator:public Iterator
{
public:
	ConcreteIterator(Aggregate *aggregate)
	{
		m_aggregate = aggregate;
		current_index = 0;
	}
	virtual void First() 
	{
		current_index = 0;
	}
	virtual void Next()
	{
		if (current_index<m_aggregate->getSize())
		{
			current_index++;
		}
	}
	virtual bool IsDone() 
	{
		return (current_index == m_aggregate->getSize());
	}
	virtual Object CurrentItem() 
	{
		return m_aggregate->getItem(current_index);
	}
private:
	int current_index;
	Aggregate *m_aggregate;
};
class ConcreteAggregate:public Aggregate
{
public:
	ConcreteAggregate()
	{
		for (int i = 0; i < SIZE; i++)
		{
			object[i] = i + 100;
		}
	}
	virtual Iterator* CreateIterator() 
	{
		return new ConcreteIterator(this);//让迭代器持有一个集合的 引用
	}
	virtual Object getItem(int index) 
	{
		return object[index];
	}
	virtual int getSize()
	{
		return SIZE;
	}
private:
	Object object[SIZE];
};

void main()
{
	Aggregate* agg = new ConcreteAggregate;
	Iterator* it = agg->CreateIterator();
	for (; !(it->IsDone()); it->Next())
	{
		cout<<it->CurrentItem()<<" ";
	}

	delete it;
	delete agg;
	system("pause");
}