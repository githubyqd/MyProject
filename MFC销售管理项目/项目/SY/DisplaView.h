#pragma once



// CDisplaView 窗体视图

class CDisplaView : public CFormView
{
	DECLARE_DYNCREATE(CDisplaView)

protected:
	CDisplaView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


