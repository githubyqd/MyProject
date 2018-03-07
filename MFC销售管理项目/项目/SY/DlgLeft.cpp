// DlgLeft.cpp : ʵ���ļ�
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


// CDlgLeft ���

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


// CDlgLeft ��Ϣ�������


void CDlgLeft::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	//������������ѡ��״̬ ��ʾ����
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//д��ͷ
	CString str[] = {TEXT("��ƷID"), TEXT("��Ʒ����"), TEXT("��Ʒ�۸�"), TEXT("�������")};
	for (int i = 0; i < sizeof(str)/sizeof(str[0]); i++)
	{
		//���ñ�ͷ������1���� 2���� 3���뷽ʽ 4�п�
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
