// BallHiveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BallHive.h"
#include "BallHiveDlg.h"
#include "Bfs.h"
#include "Cell.h"
#include "Ball.h"
#include "Mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CBallHiveApp theApp;

#define MOVE_BALL_TIMER  0x8900
#define GAME_OVER_TIMER  0x8901
#define SCORE_TIMER      0x8902
#define NEW_BALLS_TIMER  0x8903

/////////////////////////////////////////////////////////////////////////////
// CBallHiveDlg dialog

CBallHiveDlg::CBallHiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBallHiveDlg::IDD, pParent), m_BeginnerBtn(BEGINNER), m_ExpertBtn(EXPERT), m_MasterBtn(MASTER)
{
	//{{AFX_DATA_INIT(CBallHiveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	theApp.GetGame()->SetBallHiveDlg(this);
	m_bMoveDlg        = false;
	m_bBallMoving     = false;
	m_BallFlashIndex  = 0;
	m_ScoreFlashIndex = 0;
	m_MoveBallTimer   = 0;
	m_GameOverTimer   = 0;
	m_ScoreTimer      = 0;
	m_FlashTimer      = 0;
	m_pDlgAbout       = NULL;
	m_pToolTips       = NULL;
}

void CBallHiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBallHiveDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBallHiveDlg, CDialog)
	//{{AFX_MSG_MAP(CBallHiveDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBallHiveDlg message handlers

BOOL CBallHiveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// random init
	srand((unsigned)time(NULL));


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// craete the dialog RGNs (ellicptic borad + rounded rectangle for hi score)
	m_GameRgn.CreateEllipticRgn(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
	m_HiScoreRgn.CreateRoundRectRgn(BOARD_WIDTH - 75, BOARD_HEIGHT - 40, BOARD_WIDTH + 25, BOARD_HEIGHT + 25, 20, 20);
	m_AllRgn.CreateEllipticRgn(0, 0, 20, 20);
	m_AllRgn.CombineRgn(&m_GameRgn, &m_HiScoreRgn, RGN_OR);
	SetWindowRgn(m_AllRgn, true);

	// do some init
	theApp.GetGame()->Init();

	// build the exit button
	RECT rect;
	rect.left   = 286;
	rect.right  = 302;
	rect.top    = 40;
	rect.bottom = 56;
	m_ExitBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	
	// build the about button
	rect.left   = 264;
	rect.right  = 280;
	rect.top    = 40;
	rect.bottom = 56;
	m_AboutBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	
	
	// build the begiiner button
	rect.left   = 280;
	rect.right  = 339;
	rect.top    = 70;
	rect.bottom = 90;
	m_BeginnerBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);

	// build the expert button
	rect.left   = 300;
	rect.right  = 359;
	rect.top    = 100;
	rect.bottom = 120;
	m_ExpertBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);

	// build the master button
	rect.left   = 315;
	rect.right  = 374;
	rect.top    = 130;
	rect.bottom = 150;
	m_MasterBtn.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);


	// build the game over message
	rect.left   = 58;
	rect.right  = 58+264;
	rect.top    = 95;
	rect.bottom = 95+133;
	m_GameOver.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	m_GameOver.ShowWindow(SW_HIDE);
	
	// build the score display
	rect.left   = 100;
	rect.right  = 250;
	rect.top    = 315;
	rect.bottom = 335;
	m_Score.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	m_Score.ShowWindow(SW_SHOW);
	
	// build the hi score display
	rect.left   = BOARD_WIDTH - 65;
	rect.right  = BOARD_WIDTH + 15;
	rect.top    = BOARD_HEIGHT - 30;
	rect.bottom = BOARD_HEIGHT + 15;
	m_HiScore.Create(NULL, WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, this);
	m_HiScore.ShowWindow(SW_SHOW);
	

	theApp.GetGame()->Restart(BEGINNER);

	// tilte
	SetWindowText("The Hive - by Avi Sadde");

	// tooltips
	m_pToolTips = new CToolTipCtrl;
	m_pToolTips->Create(this);

	m_pToolTips->AddTool(&m_Score,       "current score");
	m_pToolTips->AddTool(&m_HiScore,     "hi score");
	m_pToolTips->AddTool(&m_BeginnerBtn, "start a new game at beginner level");
	m_pToolTips->AddTool(&m_ExpertBtn,   "start a new game at expert level");
	m_pToolTips->AddTool(&m_MasterBtn,   "start a new game at master level");
	m_pToolTips->AddTool(&m_AboutBtn,    "open an about dialog");
	m_pToolTips->AddTool(&m_ExitBtn,     "exit the Hive");

	m_pToolTips->Activate(TRUE);


	// read data from file
	ReadDataFile();

	// open about dialog (if needed)
	if(CAboutDialog::m_bOpenOnStartup)
		About(true);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBallHiveDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc( this ); // Device context for painting

		//do not call CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBallHiveDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CBallHiveDlg::Level(ELevels level)
{
	// set level buttons
	m_BeginnerBtn.Select(level == BEGINNER);
	m_ExpertBtn.Select(level == EXPERT);
	m_MasterBtn.Select(level == MASTER);
}


void CBallHiveDlg::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CBallHiveDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// moving ?
	if(m_bMoveDlg)
	{
		m_bMoveDlg = false; // stop moving!
		ReleaseCapture();
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CBallHiveDlg::OnMouseMove(UINT nFlags, CPoint point) 
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

void CBallHiveDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
		case MOVE_BALL_TIMER:
		{
			// take out the ball from the current cell 
			m_pCell->SetBall(NULL, false);

			// move ball from cell ...
			m_pCell = m_Path[m_PathIndex];

			// set the ball to move
			m_pCell->SetBall(m_pBall, false);

			// redraw the ball in the new cell
			m_pBall->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			
			// nect cell
			m_PathIndex++;

			// play sound (move)
			m_SoundPlayer.Play((char*)IDR_WAVE_MOVE, theApp.m_hInstance, false);

			// no more cells in path?
			if(m_PathIndex >= (int)m_Path.size())
			{
				// finish moving the ball 
				KillTimer(m_MoveBallTimer); // kill timer
				m_MoveBallTimer = 0; // no tiemr
				m_pCell = NULL;      // no cell to move to
				m_pBall = NULL;      // no ball to move
				m_Path.clear();      // no path
				theApp.GetGame()->Moved(); // notify the ball has moved
				m_bBallMoving = false; // ball is not moving!
			}
			break;
		}

		case GAME_OVER_TIMER:
		{
			// draw game over message
			m_GameOver.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		}

		case SCORE_TIMER:
		{
			CRect rect;
			rect.left   = 100;
			rect.right  = 250;
			rect.top    = 315;
			rect.bottom = 335;
			
			m_ScoreFlashIndex++; // add a flash
			if(m_ScoreFlashIndex == 4) // enough ?
			{
				// no flashes
				m_ScoreFlashIndex = 0;
				KillTimer(m_ScoreTimer); // kill timer
				m_ScoreTimer = 0;
				m_Score.Color(true); // draw true score color
			}
			else
				m_Score.Color(false); // draw score in flashing color

			RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			break;
		}		

		case NEW_BALLS_TIMER:
		{
			m_BallFlashIndex++; // add a flash
			if(m_BallFlashIndex == 15)// enough ?
			{
				// no flashes
				m_BallFlashIndex = 0;
				KillTimer(m_FlashTimer); // kill timer
				m_FlashTimer = 0;
				theApp.GetGame()->FlashBalls(false); // do not flash balls!
			}
			else
			{
				theApp.GetGame()->FlashBalls(true); // flash balls
			}
			break;
		}
	}	

	CDialog::OnTimer(nIDEvent);
}


void CBallHiveDlg::MoveBall(std::list<CNode*> path)
{
	// balls are flashing ?
	if(m_FlashTimer)
	{
		// stop flashing balls!
		m_BallFlashIndex = 0;
		KillTimer(m_FlashTimer);
		theApp.GetGame()->FlashBalls(false);
	}

	// the ball is moving!
	m_bBallMoving = true;

	// copy the path
	std::list<CNode*>::iterator iter = path.begin();
	for(; iter != path.end(); iter++)
	{
		CNode* p = *iter;
		m_Path.push_back(p->GetCell());
	}

	// first cell in the path
	m_pCell = m_Path[0];
	m_pBall = m_pCell->GetBall(); // ball to be moved
	
	m_PathIndex = 1; // start of path
	m_MoveBallTimer = SetTimer(MOVE_BALL_TIMER, 250, NULL); // start timer to move ball
}

void CBallHiveDlg::GameOver(bool bGameOver)
{
	// game over message 

	m_GameOver.SetWindowPos(&wndTopMost, 0,0,0,0,SWP_SHOWWINDOW | SWP_NOSIZE |SWP_NOMOVE);
	m_GameOver.ShowWindow(bGameOver ? SW_SHOW : SW_HIDE);

	// flash
	if(bGameOver)
		m_GameOverTimer = SetTimer(GAME_OVER_TIMER, 360, NULL);
	else
	{
		// earse message
		KillTimer(m_GameOverTimer);
		RedrawWindow();
	}
}


void CBallHiveDlg::Score(int score, bool add) 
{ 
	// set score (and hi score)
	m_Score.SetScore(score, add); 
	m_HiScore.SetHiScore(m_Score.GetScore()); 

	// redraw the score and hi score area
	CRect rect;
	rect.left   = 100;
	rect.right  = 250;
	rect.top    = 315;
	rect.bottom = 335;
	RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	rect.left   = BOARD_WIDTH - 65;
	rect.right  = BOARD_WIDTH + 15;
	rect.top    = BOARD_HEIGHT - 30;
	rect.bottom = BOARD_HEIGHT + 15;
	RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	// first time here?
	if(score == 0)
	{
		// just draw - do not flash
		m_Score.Color(true);
	}
	else
	{
		// flash score
		m_ScoreTimer = SetTimer(SCORE_TIMER, 60, NULL);
	}
}



void CBallHiveDlg::About(bool bOpen)
{
	// open about box?
	if(bOpen)
	{
		// already opened?
		if(m_pDlgAbout)
			return;

		// create and open
		m_pDlgAbout = new CAboutDialog;
		m_pDlgAbout->Create(IDD_DIALOG_ABOUT, this);
	}
	else
	{
		// close and destroy
		m_pDlgAbout->DestroyWindow();
		delete m_pDlgAbout;
		m_pDlgAbout = NULL;
	}
}

void CBallHiveDlg::FlashBalls()
{
	// start flashing new balls
	m_FlashTimer = SetTimer(NEW_BALLS_TIMER, 110, NULL);
}

void CBallHiveDlg::OnClose() 
{
	// kill about dialog
	if(m_pDlgAbout)
	{
		m_pDlgAbout->DestroyWindow();
		delete m_pDlgAbout;
		m_pDlgAbout = NULL;
	}

	// kill tooltips
	if(m_pToolTips)
	{
		delete m_pToolTips;
		m_pToolTips = NULL;
	}
	
	CDialog::OnClose();
}

void CBallHiveDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// kill about dialog
	if(m_pDlgAbout)
	{
		m_pDlgAbout->DestroyWindow();
		delete m_pDlgAbout;
		m_pDlgAbout = NULL;
	}

	// kill tooltips
	if(m_pToolTips)
	{
		delete m_pToolTips;
		m_pToolTips = NULL;
	}
}


BOOL CBallHiveDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pToolTips != NULL)
		m_pToolTips->RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CBallHiveDlg::ReadDataFile()
{
	long hiScore   = 0; // defualt
	char openAbout = 1; // defualt

	FILE* fp;
	fopen_s(&fp, "data", "rb");
	
	if(fp != NULL)
	{
		// read hi score
		if(fread(&hiScore, sizeof(long), 1, fp) != 1)
			hiScore   = 0;

		// read open about
		if(fread(&openAbout, sizeof(char), 1, fp) != 1)
			openAbout   = 1;

		fclose(fp);
	}

	// set hi score
	m_HiScore.SetHiScore(hiScore); 

	// set open about
	CAboutDialog::m_bOpenOnStartup = (openAbout == 0) ? false : true;
}

void CBallHiveDlg::WriteDataFile()
{
	long hiScore   = m_HiScore.GetHiScore();
	char openAbout = CAboutDialog::m_bOpenOnStartup;

	FILE* fp;
	fopen_s(&fp, "data", "wb");
	
	if(fp != NULL)
	{
		// write hi score
		fwrite(&hiScore, sizeof(long), 1, fp);

		// write open about
		fwrite(&openAbout, sizeof(char), 1, fp);
			hiScore   = 0;
			openAbout   = 1;

		fclose(fp);
	}
}

