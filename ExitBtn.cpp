// ExitBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "ExitBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExitBtn

CExitBtn::CExitBtn()
{
}

CExitBtn::~CExitBtn()
{
}


BEGIN_MESSAGE_MAP(CExitBtn, CStatic)
	//{{AFX_MSG_MAP(CExitBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExitBtn message handlers

void CExitBtn::Draw(CDC *pDC) 
{
	CBitmap bmpExit, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpExit.LoadBitmap(IDB_BITMAP_EXIT);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpExit);


	pDC->BitBlt(
		0, 
		0, 
		16, 
		16, 
		&memdc, 
		0, 
		0, 
		SRCCOPY);

	memdc.SelectObject( poldbmp );
}

void CExitBtn::OnClicked() 
{
	// Bye bye
	::PostMessage(NULL, WM_QUIT, 0, 0);
}

void CExitBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
