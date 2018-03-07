#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <afx.h>
using namespace std;

#define _F_LOGIN_ "./login.ini"
#define _F_STOCK_ "./stock.txt"

struct msg
{
	int id;
	string name;
	int price;
	int num;
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	void ReadLogin(CString &name, CString &pwd);	//��ȡ��¼��Ϣ
	void WritePwd(char *pwd, char *name);			//�޸�����
	void ReadDocline();								//��ȡ��Ʒ����
	void WriteDocline();							//д����Ʒ
	void Addline(CString name, int num, int price); //�����Ʒ
	list<msg> ls;
};

