#pragma once



// CDisplaView ������ͼ

class CDisplaView : public CFormView
{
	DECLARE_DYNCREATE(CDisplaView)

protected:
	CDisplaView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDisplaView();

public:
	enum { IDD = IDD_DISPLAVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


