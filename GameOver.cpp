// GameOver.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "GameOver.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameOver

CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}


BEGIN_MESSAGE_MAP(CGameOver, CStatic)
	//{{AFX_MSG_MAP(CGameOver)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameOver message handlers

void CGameOver::Draw(CDC *pDC) 
{
	CBitmap bmpGameOver, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpGameOver.LoadBitmap(IDB_BITMAP_GAMEOVER);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpGameOver);

	static bool bPAINT =true;
	UINT src;
	if(bPAINT)
		src = SRCPAINT;
	else
		src = SRCINVERT;

	pDC->BitBlt(
		0, 
		0, 
		264, 
		133, 
		&memdc, 
		0, 
		0, 
		src);
	bPAINT = !bPAINT;

	memdc.SelectObject( poldbmp );
}


void CGameOver::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
