/*单例模式（singleton）
保证一个类只有一个实例存在，同时提供能对该实例加以访问的全局访问方法*/

#include "windows.h"
#include "winbase.h"
#include <process.h>
#include <iostream>
using namespace std;
//static CCriticalSection cs;					// MFC定义一个临界区

class Singleton									//单例
{
private:										//构造函数私有化
	Singleton()									//c++构造函数不能保证是线程安全的
	{
		m_num++;
		printf("Singleton begin\n");
		Sleep(1000);
		printf("Singleton end\n");
	}
public:
	/*static Singleton* SingleGet()				//提供全局访问方法
	{
		if (single==NULL)//判断是否存在
		{
			single = new Singleton;				//多线程调用new Singleton无效
		}
		return single;
	}*/											//懒汉式
	static Singleton* SingleGet()
	{
		return single;
	}
	static void getM()
	{
		printf("m_num:%d\n", m_num);
	}
private:
	static Singleton* single;
	static int m_num;
};

//Singleton* Singleton::single = NULL;						//懒汉式
Singleton* Singleton::single = new Singleton;				//饿汉式
int Singleton::m_num = 0;

void threadFunc(void *p)
{
	DWORD id = GetCurrentThreadId();
	Singleton::SingleGet()->getM();
	printf("id:%d\n", id);
	return;
}

void main()
{
	//只有当我们调用时才会new出对象，在new对象时做判断===>懒汉式
	Singleton* s1 = Singleton::SingleGet();
	Singleton* s2 = Singleton::SingleGet();
	if (s1==s2)
	{
		cout<<"s1==s2"<<endl;
	}
	else
	{
		cout<<"s1!=s2"<<endl;
	}
	int threadnum = 3;
	HANDLE threadhdl[100];
	for(int i=0; i<threadnum; i++)
	{
		threadhdl[i] = (HANDLE)_beginthread(threadFunc, 0, NULL);
	}
	for(int i=0; i<threadnum; i++)//挂起主线程
	{
		WaitForSingleObject(threadhdl[i], INFINITE);
	}
	printf("main \n");							// MFC中TRACE("main \n");
	system("pause");
}
