// Score.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "Score.h"

#ifdef _DEBUG
#define Level DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBallHiveApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CScore

CScore::CScore()
{
	m_Score = 0;
	m_Color = 0;
}

CScore::~CScore()
{
}


BEGIN_MESSAGE_MAP(CScore, CStatic)
	//{{AFX_MSG_MAP(CScore)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScore message handlers

void CScore::Draw(CDC *pDC)
{

	CBitmap bmpDigit, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpDigit.LoadBitmap(IDB_BITMAP_DIGITS);


	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpDigit);

	int tmpScore = m_Score;
	int index = 0;


	do
	{
		int digit = tmpScore % 10;
		tmpScore /= 10;

		pDC->BitBlt(
			150 - 16 - index*15, 
			0, 
			15, 
			19, 
			&memdc, 
			15 * digit, 
			19 * m_Color, 
			SRCPAINT);

		index++;
	} while (tmpScore);

	memdc.SelectObject( poldbmp );
}


void CScore::SetScore(int score, bool add)
{
	if(add)
		m_Score += score;
	else
		m_Score = score;

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}



void CScore::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CScore::Color(bool bFirst)
{
	if(bFirst)
		m_Color = 0;
	else
		m_Color = (m_Color + 1) % 4;
}
