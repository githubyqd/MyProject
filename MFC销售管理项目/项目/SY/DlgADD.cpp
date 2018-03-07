// DlgADD.cpp : 实现文件
//

#include "stdafx.h"
#include "SY.h"
#include "DlgADD.h"

#include "InfoFile.h"


// CDlgADD

IMPLEMENT_DYNCREATE(CDlgADD, CFormView)

CDlgADD::CDlgADD()
	: CFormView(CDlgADD::IDD)
	, m_price1(0)
	, m_num1(0)
	, m_price2(0)
	, m_num2(0)
	, m_name2(_T(""))
{

}

CDlgADD::~CDlgADD()
{
}

void CDlgADD::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT7, m_num1);
	//  DDX_Text(pDX, IDC_EDIT10, m_name);
	DDX_Text(pDX, IDC_EDIT9, m_price2);
	DDX_Text(pDX, IDC_EDIT8, m_num2);
	DDX_Text(pDX, IDC_EDIT10, m_name2);
}

BEGIN_MESSAGE_MAP(CDlgADD, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgADD::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgADD::OnBnClickedButton6)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgADD::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgADD::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgADD::OnBnClickedButton7)
END_MESSAGE_MAP()


// CDlgADD 诊断

#ifdef _DEBUG
void CDlgADD::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgADD::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgADD 消息处理程序


void CDlgADD::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_num1 < 0)
	{
		MessageBox(TEXT("数量要大于0"));
		return;
	}
	//获取商品名称
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			it->num += m_num1;
			m_num1 = 0;
			UpdateData(FALSE);
			MessageBox(TEXT("添加成功"));
		}
	}

	//最新数据写入文件
	file.WriteDocline();
}


void CDlgADD::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num1 = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CDlgADD::OnCbnSelchangeCombo1()
{
	//根据索引获取具体内容
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			m_price1 = it->price;
			UpdateData(FALSE);
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgADD::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));
	}
	//默认选中第一个
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CDlgADD::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//验证数据有效性
	UpdateData(TRUE);
	if (m_name2.IsEmpty()||m_num2<=0||m_price2<=0)
	{
		MessageBox(TEXT("输入有误"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_num2, m_price2);
	file.WriteDocline();
	//同步左侧下拉框
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
	//清空数据
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
	MessageBox(TEXT("添加成功"));
}


void CDlgADD::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_price2 = 0;
	m_num2 = 0;
	m_name2.Empty();
	UpdateData(FALSE);
}
