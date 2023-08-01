// Cell.cpp: implementation of the CCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BallHive.h"
#include "Cell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHiveGame* CCell::m_pTheGame=NULL;

CCell::CCell()
{
	m_pBall = NULL;
	m_bSelected = false;
}

CCell::~CCell()
{

}


CBall* CCell::SetBall(CBall *pBall, bool bNewBall)
{
	// set a ball in the cell
	CBall *pRetBall = m_pBall;
	m_pBall = pBall;
	if(m_pBall)
	{
		// hey ball! I'm your cell
		m_pBall->SetCell(this);

		// are you new?
		if(bNewBall)
			pBall->Flash(true); // flash from joy!
	}

	return pRetBall;
}



BEGIN_MESSAGE_MAP(CCell, CWnd)
	//{{AFX_MSG_MAP(CCell)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCell message handlers

void CCell::Draw(CDC *pDC) 
{
	CBitmap bmpCell, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	if(m_bSelected)
		bmpCell.LoadBitmap(IDB_BITMAP_SELECTED_CELL);
	else
		bmpCell.LoadBitmap(IDB_BITMAP_CELL);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpCell);


	pDC->BitBlt(
		0, 
		0, 
		CELL_WIDTH+1, 
		CELL_HEIGHT+1, 
		&memdc, 
		0, 
		0, 
		SRCCOPY);

	memdc.SelectObject( poldbmp );
}

void CCell::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_pTheGame->Select(this);
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CCell::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CWnd::OnPaint() for painting messages
}
