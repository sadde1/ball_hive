// Board.cpp: implementation of the CBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BallHive.h"
#include "Board.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// cells in each line:
int g_cellsInLine[9] = { 5,6,7,8,9,8,7,6,5 };

CBoard::CBoard()
{

}

CBoard::~CBoard()
{

}




BEGIN_MESSAGE_MAP(CBoard, CStatic)
	//{{AFX_MSG_MAP(CBoard)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoard message handlers

void CBoard::Draw(CDC *pDC)
{
	CBitmap bmpBoard, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpBoard.LoadBitmap(IDB_BITMAP_BOARD);

	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpBoard);


	pDC->BitBlt(
		0, 
		0, 
		BOARD_WIDTH+25, 
		BOARD_HEIGHT+25, 
		&memdc, 
		0, 
		0, 
		SRCCOPY);

	memdc.SelectObject( poldbmp );
}


/////////////////







void CBoard::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
