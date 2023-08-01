// OkBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "OkBtn.h"
#include "AboutDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COkBtn

COkBtn::COkBtn()
{
}

COkBtn::~COkBtn()
{
}


BEGIN_MESSAGE_MAP(COkBtn, CStatic)
	//{{AFX_MSG_MAP(COkBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COkBtn message handlers

void COkBtn::Draw(CDC *pDC) 
{
	CBitmap bmpOk, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpOk.LoadBitmap(IDB_BITMAP_OK);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpOk);


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

void COkBtn::OnClicked() 
{
	m_pDialog->OK();
}

void COkBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}


void COkBtn::SetDialog(CAboutDialog *pDialog)
{
	m_pDialog = pDialog;
}
