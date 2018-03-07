#pragma once
#include "afxwin.h"



// CDlgADD 窗体视图

class CDlgADD : public CFormView
{
	DECLARE_DYNCREATE(CDlgADD)

protected:
	CDlgADD();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgADD();

public:
	enum { IDD = DIALOG_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo;
	int m_price1;
	int m_num1;
//	CString m_name;
	int m_price2;
	int m_num2;
	CString m_name2;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnCbnSelchangeCombo1();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
};


