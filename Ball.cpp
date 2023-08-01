// Ball.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "Ball.h"
#include "Cell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBall

// color of balls
int g_BallBitmaps[NUM_OF_BALL_COLORS] = { 
	IDB_BITMAP_RED_BALL,
	IDB_BITMAP_GREEN_BALL,
	IDB_BITMAP_DARK_BLUE_BALL,
	IDB_BITMAP_LIGHT_BLUE_BALL,
	IDB_BITMAP_BROWN_BALL,
	IDB_BITMAP_ORANGE_BALL,
	IDB_BITMAP_PINK_BALL,
	IDB_BITMAP_GRAY_BALL
};

CBall::CBall()
{
	m_color         = RED_BALL; // just so it has legal value!
	m_bFlash        = false;    // no flashing at this stage
	m_bRegularColor = true;     // no flashing at this stage - so regular color
}


CBall::~CBall()
{
}


BEGIN_MESSAGE_MAP(CBall, CWnd)
	//{{AFX_MSG_MAP(CBall)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBall message handlers

void CBall::Draw(CDC *pDC)
{
	CBitmap bmpBall, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	if(m_bRegularColor)
		bmpBall.LoadBitmap(g_BallBitmaps[m_color]);
	else
		bmpBall.LoadBitmap(IDB_BITMAP_FLASH_BALL); // flashed color (white)

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpBall);

	pDC->BitBlt(
		0, 
		0, 
		25, 
		25, 
		&memdc, 
		0, 
		0, 
		SRCCOPY);

	memdc.SelectObject( poldbmp );
}

void CBall::SetCell(CCell *pCell) 
{ 
	// put ball in cell
	m_pCell = pCell; 

	// place on board
	m_X = BOARD_WIDTH/2+ m_pCell->GetIndexInLine()*CELL_WIDTH - g_cellsInLine[m_pCell->GetLine()]*CELL_HEIGHT/2 - 12;
	m_Y = (BOARD_HEIGHT - 7 * CELL_HEIGHT)/2 + m_pCell->GetLine()*28 - 2;

	RECT rect;
	rect.left   = m_X;
	rect.top    = m_Y;
	rect.right  = m_X + 20;
	rect.bottom = m_Y + 20;

	// actual placing
	MoveWindow(m_X, m_Y, 20, 20, true);

	// make it round
	CRgn rgn;
	rgn.CreateEllipticRgn(0,0,20,20);
	SetWindowRgn(rgn, true);

	// show!
	ShowWindow(SW_SHOW);
}

void CBall::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CWnd::OnPaint() for painting messages
}


void CBall::Flash(bool bFlash)
{
	m_bFlash = bFlash;

	// stop flashing
	if(!m_bFlash)
		m_bRegularColor = true; // set to regular color

	RedrawWindow();
}
