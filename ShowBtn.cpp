// ShowBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "ShowBtn.h"
#include "BallHiveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBallHiveApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CShowBtn

CShowBtn::CShowBtn()
{
}

CShowBtn::~CShowBtn()
{
}


BEGIN_MESSAGE_MAP(CShowBtn, CStatic)
	//{{AFX_MSG_MAP(CShowBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowBtn message handlers

void CShowBtn::Draw(CDC *pDC) 
{
	CBitmap bmpShow, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	if(CAboutDialog::m_bOpenOnStartup)
		bmpShow.LoadBitmap(IDB_BITMAP_SHOW);
	else
		bmpShow.LoadBitmap(IDB_BITMAP_NOT_SHOW);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpShow);


	pDC->BitBlt(
		0, 
		0, 
		93, 
		16, 
		&memdc, 
		0, 
		0, 
		SRCCOPY);

	memdc.SelectObject( poldbmp );
}

void CShowBtn::OnClicked() 
{
	CAboutDialog::m_bOpenOnStartup = !CAboutDialog::m_bOpenOnStartup;
	RedrawWindow();
	theApp.GetGame()->GetBallHiveDlg()->WriteDataFile();
}

void CShowBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
