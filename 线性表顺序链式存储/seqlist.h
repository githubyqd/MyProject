//建造者模式（Builder）					

#include <iostream>
using namespace std;
#include "string"
class House
{
public:
	void setDoor(string door)
	{
		m_door = door;
	}
	void setWindow(string window)
	{
		m_window = window;
	}

	string getDoor()
	{
		cout<<m_door<<endl;
		return m_door;
	}
	string getWindow()
	{
		cout<<m_window<<endl;
		return m_window;
	}
private:
	string m_door;
	string m_window;
};
class Build
{
public:
	Build()
	{
		m_house = new House;
	}
	void makeBuild()
	{
		BuildDoor(m_house);
		BuildWindow(m_house);
	}
	void BuildDoor(House* h)
	{
		h->setDoor("门");
	}
	void BuildWall(House* h)
	{
		h->setWall("墙");
	}
	void BuildWindow(House* h)
	{
		h->setWindow("窗");
	}
	House* getHouse()
	{
		return m_house;
	}
private:
	House* m_house;
};

class Builder
{
public:
	virtual void BuildDoor() = 0;
	virtual void BuildWindow() = 0;
	virtual House* getHouse() = 0;
};
//公寓工程类
class FlatBuilder:public Builder
{
public:
	FlatBuilder()
	{
		m_house = new House;
	}
	virtual void BuildDoor()
	{
		m_house->setDoor("flat door");
	}
	virtual void BuildWindow() 
	{
		m_house->setWindow("flat window");
	}
	virtual House* getHouse() 
	{
		return m_house;
	}
private:
	House* m_house;
};
//别墅工程类
class VillBuilder:public Builder
{
public:
	VillBuilder()
	{
		m_house = new House;
	}
	virtual void BuildDoor()
	{
		m_house->setDoor("Vill door");
	}
	virtual void BuildWindow() 
	{
		m_house->setWindow("Vill window");
	}
	virtual House* getHouse() 
	{
		return m_house;
	}
private:
	House* m_house;
};
//设计师负责建造逻辑
class Director
{
public:
	Director(Builder* build)
	{
		m_build = build;
	}
	void construct()
	{
		m_build->BuildWindow();
		m_build->BuildDoor();
	}
private:
	Builder* m_build;
};

void main()
{
	House* house =  NULL;
	Director* director = NULL;
	VillBuilder* builder = NULL;

	builder = new VillBuilder;
	director = new Director(builder);
	director->construct();
	house =  builder->getHouse();
	house->getDoor();
		
	delete builder;
	delete director;
	delete house;
	system("pause");
}