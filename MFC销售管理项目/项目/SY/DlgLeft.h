#pragma once
#include "afxcmn.h"



// CDlgLeft ������ͼ

class CDlgLeft : public CFormView
{
	DECLARE_DYNCREATE(CDlgLeft)

protected:
	CDlgLeft();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
};


