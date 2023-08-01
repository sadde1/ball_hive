// AboutBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "AboutBtn.h"
#include "AboutDialog.h"
#include "BallHiveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBallHiveApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutBtn

CAboutBtn::CAboutBtn()
{
}

CAboutBtn::~CAboutBtn()
{
}


BEGIN_MESSAGE_MAP(CAboutBtn, CStatic)
	//{{AFX_MSG_MAP(CAboutBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutBtn message handlers

// draw the about button bitmap
void CAboutBtn::Draw(CDC *pDC) 
{
	CBitmap bmpAbout, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpAbout.LoadBitmap(IDB_BITMAP_ABOUT);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpAbout);


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

void CAboutBtn::OnClicked() 
{
	// when clicked - open the about dialog box
	theApp.GetGame()->GetBallHiveDlg()->About(true);
}

void CAboutBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
