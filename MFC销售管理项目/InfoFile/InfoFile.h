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

	void ReadLogin(CString &name, CString &pwd);	//读取登录信息
	void WritePwd(char *pwd, char *name);			//修改密码
	void ReadDocline();								//读取商品数据
	void WriteDocline();							//写入商品
	void Addline(CString name, int num, int price); //添加商品
	list<msg> ls;
};

