#include "stdafx.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
}
CInfoFile::~CInfoFile()
{
}

void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs;//�������
	ifs.open(_F_LOGIN_);
	char buf[1024] = {0};
	ifs.getline(buf, sizeof(buf));
	name = CString(buf);

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close();
}

void CInfoFile::WritePwd(char *name, char *pwd)
{
	ofstream ofs;
	ofs.open(_F_LOGIN_);
	ofs << name << endl;
	ofs << pwd << endl;
	ofs.close();
}			

void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK_);//���뷽ʽ���ļ�
	char buf[1024] = {0};
	ls.clear();

	ifs.getline(buf, sizeof(buf));//��ͷ
	while (!ifs.eof())
	{
		msg tmp;
		ifs.getline(buf, sizeof(buf));
		char *sst = strtok(buf, "|");//��|�и�
		if (sst != NULL)
		{
			tmp.id = atoi(sst);
		}
		else
		{
			break;
		}
		sst = strtok(NULL, "|");
		tmp.name = sst;
		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);
		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);
		
		ls.push_back(tmp);
	}
	ifs.close();
}	

void CInfoFile::WriteDocline()
{
	ofstream ofs(_F_STOCK_);
	if (ls.size() > 0)
	{
		ofs << "��ƷID|��Ʒ����|��Ʒ�۸�|���|" << endl;//д���ͷ
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << "|" <<endl;
		}
	}
	ofs.close();
}	

void CInfoFile::Addline(CString name, int num, int price)
{
	CStringA tmp;
	tmp	= name;
	char buf[1024] = {0};	
	strcpy(buf, tmp.GetBuffer(0));
	FILE *fp = fopen(_F_STOCK_, "a+");
	fprintf(fp, "%d|%s|%d|%d|", ls.size()+1, buf, price, num);//��ĩβ��һ��
}
