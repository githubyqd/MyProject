#pragma once
#include "afxwin.h"



// CDlgDel ������ͼ

class CDlgDel : public CFormView
{
	DECLARE_DYNCREATE(CDlgDel)

protected:
	CDlgDel();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDlgDel();

public:
	enum { IDD = DIALOG_DEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
private:
	CComboBox m_combo;
	int m_price;
	int m_num;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};


