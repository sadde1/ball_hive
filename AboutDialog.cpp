// AboutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ballhive.h"
#include "AboutDialog.h"
#include "BallHiveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBallHiveApp theApp;

#define PAINT_TIMER 0x8911

bool CAboutDialog::m_bOpenOnStartup = true;

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog


CAboutDialog::CAboutDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// the dialog is not moving (yet)
	m_bMoveDlg = false;
}


void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDialog, CDialog)
	//{{AFX_MSG_MAP(CAboutDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers


BOOL CAboutDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// build a hexagon RGN
	POINT points[7] = { {70,0}, {380,0}, {450,170}, {380,340}, {70,340}, {0,170}, {70,0} };
	m_rgn.CreatePolygonRgn(points, 7, WINDING);
	SetWindowRgn(m_rgn, true);

	// build the OK button
	RECT rect;
	rect.left   = 390;
	rect.right  = 406;
	rect.top    = 160;
	rect.bottom = 176;
	m_OkBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	m_OkBtn.SetDialog(this); // let the button know this dialog

	// build the show on startup button
	rect.left   = 100;
	rect.right  = 393;
	rect.top    = 310;
	rect.bottom = 326;
	m_ShowBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);

	// build the pause/continue button
	rect.left   = 414;
	rect.right  = 430;
	rect.top    = 160;
	rect.bottom = 176;
	m_PauseBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	m_PauseBtn.SetDialog(this);

	// build the foreground (the scrolling area)
	rect.left   = 75;
	rect.right  = 375;
	rect.top    = 55;
	rect.bottom = 305;
	m_Fgr.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);

	// scroll every 60 mSec
	m_PaintTimer = SetTimer(PAINT_TIMER, 50, NULL);

	// title 
	SetWindowText("About The Hive");

	// tooltips
	m_pToolTips = new CToolTipCtrl;
	m_pToolTips->Create(this);

	m_pToolTips->AddTool(&m_OkBtn,    "close the about dialog");
	m_pToolTips->AddTool(&m_PauseBtn, "pause or continue the scrolling");
	m_pToolTips->AddTool(&m_ShowBtn,  "show (or not) this dialog at startup");

	m_pToolTips->Activate(TRUE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CAboutDialog::OK()
{
	// done with the about dialog
	theApp.GetGame()->GetBallHiveDlg()->About(false);
}


void CAboutDialog::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
		case PAINT_TIMER:
		{
			m_Fgr.RedrawWindow();
			break;
		}		
	}	

	CDialog::OnTimer(nIDEvent);
}



void CAboutDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// click on title ?
	if(point.y < 32)
	{
		m_bMoveDlg = true;  // moving!
		SetCapture();
		m_MovePnt = point; // click on point 
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CAboutDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// moving ?
	if(m_bMoveDlg)
	{
		m_bMoveDlg = false; // stop moving!
		ReleaseCapture();
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CAboutDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetWindowRect(&rect);

	// moving ?
	if(m_bMoveDlg)
	{
		// move to ...
		int left = point.x - m_MovePnt.x;
		int up   = point.y - m_MovePnt.y;

		// actual move window
		SetWindowPos(&wndTop, rect.left + left, rect.top + up, rect.bottom, rect.bottom, 0);
	}
	
	CDialog::OnMouseMove(nFlags, point);
}


void CAboutDialog::Pause(bool bPause)
{
	// pause ?
	if(bPause)
	{
		// kill timer of scrolling
		KillTimer(m_PaintTimer);
		m_PaintTimer = 0;
	}
	else // continue!
	{
		// set scrolling timer
		if(m_PaintTimer == 0)
			m_PaintTimer = SetTimer(PAINT_TIMER, 47, NULL);
	}
}


void CAboutDialog::OnClose() 
{
	// kill tooltips
	if(m_pToolTips)
	{
		delete m_pToolTips;
		m_pToolTips = NULL;
	}
	
	CDialog::OnClose();
}

void CAboutDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// kill tooltips
	if(m_pToolTips)
	{
		delete m_pToolTips;
		m_pToolTips = NULL;
	}
}


BOOL CAboutDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pToolTips != NULL)
		m_pToolTips->RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

