// PauseBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "PauseBtn.h"
#include "AboutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPauseBtn

CPauseBtn::CPauseBtn()
{
	m_bPause = false;
}

CPauseBtn::~CPauseBtn()
{
}


BEGIN_MESSAGE_MAP(CPauseBtn, CStatic)
	//{{AFX_MSG_MAP(CPauseBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPauseBtn message handlers

void CPauseBtn::Draw(CDC *pDC) 
{
	CBitmap bmpPause, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	if(m_bPause)
		bmpPause.LoadBitmap(IDB_BITMAP_CONTINUE);
	else
		bmpPause.LoadBitmap(IDB_BITMAP_PAUSE);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpPause);


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

void CPauseBtn::OnClicked() 
{
	m_bPause = !m_bPause;
	RedrawWindow();
	m_pDialog->Pause(m_bPause);
}

void CPauseBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}


void CPauseBtn::SetDialog(CAboutDialog *pDialog)
{
	m_pDialog = pDialog;
}
