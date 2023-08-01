// LevelBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "LevelBtn.h"

#ifdef _DEBUG
#define Level DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBallHiveApp theApp;

int g_Selected[3] = {IDB_BITMAP_BEGINNER_SELECTED, IDB_BITMAP_EXPERT_SELECTED, IDB_BITMAP_MASTER_SELECTED };
int g_NonSelected[3] = { IDB_BITMAP_BEGINNER, IDB_BITMAP_EXPERT, IDB_BITMAP_MASTER};

/////////////////////////////////////////////////////////////////////////////
// CLevelBtn

CLevelBtn::CLevelBtn(ELevels level) : m_Level(level)
{
}

CLevelBtn::~CLevelBtn()
{
}


BEGIN_MESSAGE_MAP(CLevelBtn, CStatic)
	//{{AFX_MSG_MAP(CLevelBtn)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLevelBtn message handlers

void CLevelBtn::Draw(CDC *pDC)
{
	CBitmap bmpLevel, *poldbmp;
	CDC memdc;

	// Load the bitmap resource
	if(m_bSelected)
		bmpLevel.LoadBitmap(g_Selected[m_Level]);
	else
		bmpLevel.LoadBitmap(g_NonSelected[m_Level]);


	// Create a compatible memory DC
	memdc.CreateCompatibleDC(pDC);

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmpLevel);


	pDC->BitBlt(
		0, 
		0, 
		59, 
		20, 
		&memdc, 
		0, 
		0, 
		SRCCOPY);

	memdc.SelectObject( poldbmp );
}

void CLevelBtn::OnClicked() 
{
	theApp.GetGame()->Restart(m_Level);
}


void CLevelBtn::Select(bool Selected)
{
	m_bSelected = Selected;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}


void CLevelBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Draw(&dc);
	
	// Do not call CStatic::OnPaint() for painting messages
}
