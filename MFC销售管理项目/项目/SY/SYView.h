
// SYView.h : CSYView ��Ľӿ�
//

#pragma once


class CSYView : public CView
{
protected: // �������л�����
	CSYView();
	DECLARE_DYNCREATE(CSYView)

// ����
public:
	CSYDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSYView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SYView.cpp �еĵ��԰汾
inline CSYDoc* CSYView::GetDocument() const
   { return reinterpret_cast<CSYDoc*>(m_pDocument); }
#endif

