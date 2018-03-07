// DlgLeft.cpp : 实现文件
//

#include "stdafx.h"
#include "SY.h"
#include "DlgLeft.h"
#include "InfoFile.h"

// CDlgLeft

IMPLEMENT_DYNCREATE(CDlgLeft, CFormView)

CDlgLeft::CDlgLeft()
	: CFormView(CDlgLeft::IDD)
{

}

CDlgLeft::~CDlgLeft()
{
}

void CDlgLeft::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CDlgLeft, CFormView)
END_MESSAGE_MAP()


// CDlgLeft 诊断

#ifdef _DEBUG
void CDlgLeft::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgLeft::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgLeft 消息处理程序


void CDlgLeft::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//设置属性整行选中状态 显示网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//写表头
	CString str[] = {TEXT("商品ID"), TEXT("商品名称"), TEXT("商品价格"), TEXT("库存数量")};
	for (int i = 0; i < sizeof(str)/sizeof(str[0]); i++)
	{
		//设置表头，参数1索引 2内容 3对齐方式 4列宽
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 90);
	}
	CInfoFile file;
	file.ReadDocline();
	CString strt;
	int i = 0;
	for (list<msg>::iterator it = file.ls.begin();it != file.ls.end(); it++)
	{
		int j = 0;
		strt.Format(_T("%d"), it->id);
		m_list.InsertItem(i, strt);

		m_list.SetItemText(i, ++j, CString(it->name.c_str()));

		strt.Format(TEXT("%d"), it->price);
		m_list.SetItemText(i, ++j, strt);

		strt.Format(TEXT("%d"), it->num);
		m_list.SetItemText(i, ++j, strt);
		i++;
	}
}
