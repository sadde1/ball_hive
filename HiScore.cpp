// HiScore.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "HiScore.h"
#include "BallHiveDlg.h"

#ifdef _DEBUG
#define Level DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBallHiveApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHiScore

CHiScore::CHiScore()
{
	m_HiScore = 0;
}

CHiScore::~CHiScore()
{
}


BEGIN_MESSAGE_MAP(CHiScore, CStatic)
	//{{AFX_MSG_MAP(CHiScore)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHiScore message handlers

void CHiScore::Draw(CDC *pDC)
{

	CBitmap bmpDigit, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	bmpDigit.LoadBitmap(IDB_BITMAP_DIGITS);


	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpDigit);

	int tmpHiScore = m_HiScore;
	int index = 0;

	// draw from low digit to hi
	do
	{
		int digit = tmpHiScore % 10; // the digit is
		tmpHiScore /= 10; // throw the lowest digit!

		pDC->BitBlt(
			80 - 16 - index*15, 
			20, 
			15, 
			19, 
			&memdc, 
			15 * digit, 
			19, 
			SRCPAINT);

		index++;
	} while (tmpHiScore);

	memdc.SelectObject( poldbmp );
}


void CHiScore::SetHiScore(int score)
{
	if(score <= m_HiScore)
		return;
	m_HiScore = score;

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	theApp.GetGame()->GetBallHiveDlg()->WriteDataFile(); // write new hi score to file 
}


int CHiScore::GetHiScore()
{
	return m_HiScore;
}


void CHiScore::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
