/*����ģʽ��singleton��
��֤һ����ֻ��һ��ʵ�����ڣ�ͬʱ�ṩ�ܶԸ�ʵ�����Է��ʵ�ȫ�ַ��ʷ���*/

#include "windows.h"
#include "winbase.h"
#include <process.h>
#include <iostream>
using namespace std;
//static CCriticalSection cs;					// MFC����һ���ٽ���

class Singleton									//����
{
private:										//���캯��˽�л�
	Singleton()									//c++���캯�����ܱ�֤���̰߳�ȫ��
	{
		m_num++;
		printf("Singleton begin\n");
		Sleep(1000);
		printf("Singleton end\n");
	}
public:
	/*static Singleton* SingleGet()				//�ṩȫ�ַ��ʷ���
	{
		if (single==NULL)//�ж��Ƿ����
		{
			single = new Singleton;				//���̵߳���new Singleton��Ч
		}
		return single;
	}*/											//����ʽ
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

//Singleton* Singleton::single = NULL;						//����ʽ
Singleton* Singleton::single = new Singleton;				//����ʽ
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
	//ֻ�е����ǵ���ʱ�Ż�new��������new����ʱ���ж�===>����ʽ
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
	for(int i=0; i<threadnum; i++)//�������߳�
	{
		WaitForSingleObject(threadhdl[i], INFINITE);
	}
	printf("main \n");							// MFC��TRACE("main \n");
	system("pause");
}
