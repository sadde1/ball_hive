// AboutFgr.cpp: implementation of the CAboutFgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BallHive.h"
#include "AboutFgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CAboutFgr::CAboutFgr()
{
	// start scroll from 0
	m_Y = 0;
}

CAboutFgr::~CAboutFgr()
{

}




BEGIN_MESSAGE_MAP(CAboutFgr, CStatic)
	//{{AFX_MSG_MAP(CAboutFgr)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutFgr message handlers

void CAboutFgr::Draw(CDC *pDC)
{
	CBitmap bmpAboutFgr, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpAboutFgr.LoadBitmap(IDB_BITMAP_ABOUTFGR);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpAboutFgr);

	pDC->BitBlt(
		0, 
		0, 
		300, 
		250, 
		&memdc, 
		0, 
		m_Y, 
		SRCCOPY);
	
	m_Y++; // advance scroll by 1 unit (y)

	memdc.SelectObject(poldbmp);
	
	// end of scroll ?
	if(m_Y > 1070)
		m_Y = 0; // start all over
}


void CAboutFgr::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}


