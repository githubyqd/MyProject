#pragma once
#include "afxcmn.h"



// CDlgLeft 窗体视图

class CDlgLeft : public CFormView
{
	DECLARE_DYNCREATE(CDlgLeft)

protected:
	CDlgLeft();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgLeft();

public:
	enum { IDD = DIALOG_Left };
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
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
};


