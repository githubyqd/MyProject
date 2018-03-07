// DlgDel.cpp : 实现文件
//

#include "stdafx.h"
#include "SY.h"
#include "DlgDel.h"
#include "InfoFile.h"

#include "MainFrm.h"


// CDlgDel

IMPLEMENT_DYNCREATE(CDlgDel, CFormView)

CDlgDel::CDlgDel()
	: CFormView(CDlgDel::IDD)
	, m_price(0)
	, m_num(0)
{

}

CDlgDel::~CDlgDel()
{
}

void CDlgDel::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
}

BEGIN_MESSAGE_MAP(CDlgDel, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgDel::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgDel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgDel::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgDel 诊断

#ifdef _DEBUG
void CDlgDel::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgDel::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgDel 消息处理程序


void CDlgDel::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, str);
	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it= file.ls.begin();it != file.ls.end(); it++)
	{
		if (str == CString(it->name.c_str()))
		{
			m_price = it->price;
		}
	}
	UpdateData(FALSE);
}


void CDlgDel::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it= file.ls.begin();it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CDlgDel::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, str);
	CInfoFile file;
	file.ReadDocline();
	if(m_num < 0)
	{
		MessageBox(TEXT("数量不能小于0"));
		return;
	}
	for(list<msg>::iterator it= file.ls.begin();it != file.ls.end(); it++)
	{
		if ((str == CString(it->name.c_str())) && (m_num < it->num))
		{
			it->num -= m_num;
			break;
		}
		if((str == CString(it->name.c_str())) && (m_num >= it->num))
		{
			file.ls.erase(it);
			m_combo.DeleteString(index);
			m_combo.SetCurSel(0);
			break;
		}
	
	}
	file.WriteDocline();
	m_num = 0;
	UpdateData(FALSE);
	OnCbnSelchangeCombo1();
	MessageBox(TEXT("删除成功"));
}


void CDlgDel::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num = 0;
	UpdateData(FALSE);
}
