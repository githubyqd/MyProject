// DlgADD.cpp : ʵ���ļ�
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


// CDlgADD ���

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


// CDlgADD ��Ϣ�������


void CDlgADD::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if (m_num1 < 0)
	{
		MessageBox(TEXT("����Ҫ����0"));
		return;
	}
	//��ȡ��Ʒ����
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
			MessageBox(TEXT("��ӳɹ�"));
		}
	}

	//��������д���ļ�
	file.WriteDocline();
}


void CDlgADD::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_num1 = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
}


void CDlgADD::OnCbnSelchangeCombo1()
{
	//����������ȡ��������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlgADD::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));
	}
	//Ĭ��ѡ�е�һ��
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CDlgADD::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��֤������Ч��
	UpdateData(TRUE);
	if (m_name2.IsEmpty()||m_num2<=0||m_price2<=0)
	{
		MessageBox(TEXT("��������"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_num2, m_price2);
	file.WriteDocline();
	//ͬ�����������
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
	//�������
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
	MessageBox(TEXT("��ӳɹ�"));
}


void CDlgADD::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_price2 = 0;
	m_num2 = 0;
	m_name2.Empty();
	UpdateData(FALSE);
}
