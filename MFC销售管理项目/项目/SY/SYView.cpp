
// SYView.cpp : CSYView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SY.h"
#endif

#include "SYDoc.h"
#include "SYView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSYView

IMPLEMENT_DYNCREATE(CSYView, CView)

BEGIN_MESSAGE_MAP(CSYView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSYView ����/����

CSYView::CSYView()
{
	// TODO: �ڴ˴���ӹ������

}

CSYView::~CSYView()
{
}

BOOL CSYView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSYView ����

void CSYView::OnDraw(CDC* /*pDC*/)
{
	CSYDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSYView ��ӡ

BOOL CSYView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSYView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSYView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CSYView ���

#ifdef _DEBUG
void CSYView::AssertValid() const
{
	CView::AssertValid();
}

void CSYView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSYDoc* CSYView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSYDoc)));
	return (CSYDoc*)m_pDocument;
}
#endif //_DEBUG


// CSYView ��Ϣ�������
