// DisplaView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SY.h"
#include "DisplaView.h"


// CDisplaView

IMPLEMENT_DYNCREATE(CDisplaView, CFormView)

CDisplaView::CDisplaView()
	: CFormView(CDisplaView::IDD)
{

}

CDisplaView::~CDisplaView()
{
}

void CDisplaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDisplaView, CFormView)
END_MESSAGE_MAP()


// CDisplaView ���

#ifdef _DEBUG
void CDisplaView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDisplaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDisplaView ��Ϣ�������
