// TabSheet.cpp : implementation file
//

#include "stdafx.h"
#include "TabSheet.h"
//#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabSheet

CTabSheet::CTabSheet()
{
    m_nNumOfPages = 0;
    m_nCurrentPage = 0;
    
//  m_brushBackground.CreateSolidBrush(::GetSysColor(COLOR_3DFACE)); //灰色
    
}

CTabSheet::~CTabSheet()
{
    if(m_brushBackground.GetSafeHandle())
        m_brushBackground.DeleteObject(); 
    
}

void CTabSheet::SetBkColor(UINT bkID)
{       
    if(m_brushBackground.GetSafeHandle())
        m_brushBackground.DeleteObject(); 
    CBitmap bmp;
    bmp.LoadBitmap(bkID);
    m_brushBackground.CreatePatternBrush(&bmp); 
    bmp.DeleteObject();

}

void CTabSheet::PreSubclassWindow() 
{ 
  //CTabCtrl::ModifyStyle(0, TCS_OWNERDRAWFIXED);  //自绘标签
  CTabCtrl::PreSubclassWindow(); 
} 


BEGIN_MESSAGE_MAP(CTabSheet, CTabCtrl)
    //{{AFX_MSG_MAP(CTabSheet)
    ON_WM_LBUTTONDOWN()
    ON_WM_DRAWITEM() 
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabSheet message handlers

BOOL CTabSheet::AddPage(LPCTSTR title, CDialog *pDialog,UINT ID)
{
    if( MAXPAGE == m_nNumOfPages )
        return FALSE;

    m_nNumOfPages++;

    m_pPages[m_nNumOfPages-1] = pDialog;
    m_IDD[m_nNumOfPages-1] = ID;
    m_Title[m_nNumOfPages-1] = title;

    return TRUE;
}

void CTabSheet::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)  
{ 
    // TODO: Add your message handler code here and/or call default 
    TRACE("nIDCtl:%d\n",nIDCtl); 
    
    CTabCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct); 
} 

void CTabSheet::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{  
        
    //  TRACE("item:%d\n",lpDrawItemStruct->itemID);    
    if(m_nNumOfPages <= 0 ) return; 
    
    /*
        char     szTabText[100];           
        TC_ITEM  tci;      
        memset(szTabText,   '\0',   sizeof(szTabText));      
        tci.mask                 =   TCIF_TEXT;      
        tci.pszText         =   szTabText;      
        tci.cchTextMax     =   sizeof(szTabText)-1;      
        
        GetItem(lpDrawItemStruct->itemID, &tci);      
    */

    
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);      

    CRect rect; 
    GetClientRect(rect);
    
    //rect = lpDrawItemStruct->rcItem; 
    
    CRect itemRect; 
    GetItemRect(m_nNumOfPages-1, &itemRect);//获得最后一个标签头坐标
    rect.left = itemRect.right;
    rect.bottom = itemRect.bottom;

    if(m_brushBackground.GetSafeHandle()) 
    {       
        pDC->FillRect(rect,&m_brushBackground); //填充除去标签的其他部分
    }
    
    pDC->SetBkMode(TRANSPARENT); //背景透明

    for(int i=0;i<m_nNumOfPages;i++)
    {       
        GetItemRect(i, &itemRect);
    
        itemRect.left += 2;
        itemRect.top += 1;
        itemRect.bottom -= 2;
        itemRect.right -= 2;

        if(m_brushBackground.GetSafeHandle()) 
        {
            pDC->FillRect(itemRect,&m_brushBackground); //标签背景
        }

        TextOut(lpDrawItemStruct->hDC,      
            itemRect.left+2,      
            itemRect.top+2,      
            m_Title[i] ,      
            lstrlen(m_Title[i]));  
    
    }
        
} 

void CTabSheet::SetRect()
{
    CRect tabRect, itemRect;
    int nX, nY, nXc, nYc;

    GetClientRect(&tabRect);
    GetItemRect(0, &itemRect);

    nX=itemRect.left;
    nY=itemRect.bottom+1;
    nXc=tabRect.right-itemRect.left-2;
    nYc=tabRect.bottom-nY-2;

    m_pPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
    
    for( int nCount=1; nCount < m_nNumOfPages; nCount++ )
        m_pPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
    
}

void CTabSheet::Show()
{

    for( int i=0; i < m_nNumOfPages; i++ )
    {
        m_pPages[i]->Create( m_IDD[i], this );
        InsertItem( i, m_Title[i] );
    }

    m_pPages[0]->ShowWindow(SW_SHOW);
    for(int i=1; i < m_nNumOfPages; i++)
        m_pPages[i]->ShowWindow(SW_HIDE);
    
    SetRect();

}

void CTabSheet::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CTabCtrl::OnLButtonDown(nFlags, point);

    if(m_nCurrentPage != GetCurFocus())
    {
        m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
        m_nCurrentPage=GetCurFocus();
        m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
//      m_pPages[m_nCurrentPage]->SetFocus();
    }
}

int CTabSheet::SetCurSel(int nItem)
{
    if( nItem < 0 || nItem >= m_nNumOfPages)
        return -1;

    int ret = m_nCurrentPage;

    if(m_nCurrentPage != nItem )
    {
        m_pPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
        m_nCurrentPage = nItem;
        m_pPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
//      m_pPages[m_nCurrentPage]->SetFocus();
        CTabCtrl::SetCurSel(nItem);
    }
        
    return ret;
}

int CTabSheet::GetCurSel()
{
    return CTabCtrl::GetCurSel();
}


BOOL CTabSheet::OnEraseBkgnd(CDC* pDC)    
{   
    if(m_nNumOfPages <= 0 ) return false; 

    return TRUE;
    
    if(!m_brushBackground.GetSafeHandle()) 
    {
        return CTabCtrl::OnEraseBkgnd(pDC);
    }
    
    CRect rect; 
    GetClientRect(rect);    
    CRect itemRect; 
    GetItemRect(m_nNumOfPages-1, &itemRect);//获得最后一个标签头坐标

    rect.bottom = itemRect.bottom;
    
    
    pDC->FillRect(rect,&m_brushBackground);  

    return true;   
}  
