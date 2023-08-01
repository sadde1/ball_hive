// BallHiveDlg.h : header file
//

#if !defined(AFX_BALLHIVEDLG_H__CC7A1762_ED54_4F0C_8EDA_AACFCAA65172__INCLUDED_)
#define AFX_BALLHIVEDLG_H__CC7A1762_ED54_4F0C_8EDA_AACFCAA65172__INCLUDED_

#include "ExitBtn.h"	// Added by ClassView
#include "AboutBtn.h"	// Added by ClassView
#include "LevelBtn.h"	// Added by ClassView
#include "GameOver.h"	// Added by ClassView
#include "Score.h"
#include "HiScore.h"
#include "SoundPlayer.h"
#include <list>
#include <vector>
#include "AboutDialog.h"

class CCell;
class CBall;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBallHiveDlg dialog

class CBallHiveDlg : public CDialog
{
	CRgn   m_GameRgn;            // region of the dialog (not a rect!)
	CRgn   m_HiScoreRgn;
	CRgn   m_AllRgn;
	bool   m_bMoveDlg;       // move the dialog
	bool   m_bBallMoving;        // is the ball moving
	CPoint m_MovePnt;        // move the dialog to
	UINT   m_MoveBallTimer;  // timer - moving the ball
	UINT   m_GameOverTimer;  //
	UINT   m_ScoreTimer; //
	UINT   m_FlashTimer;
	int    m_PathIndex;      // which ball is moving
	CBall *m_pBall;          // which ball is moving
	CCell *m_pCell;          // which ball is moving
	std::vector<CCell*> m_Path;
	CAboutDialog *m_pDlgAbout;
	int    m_BallFlashIndex;
	int    m_ScoreFlashIndex;
public:
	CSoundPlayer m_SoundPlayer;

// Construction
public:
	CBallHiveDlg(CWnd* pParent = NULL);	// standard constructor

	void MoveBall(std::list<CNode*> path);
	void GameOver(bool bGameOver);
	void Score(int score, bool add);

	void Level(ELevels level);
	bool IsMoving() { return m_bBallMoving; }

	void About(bool bOpen);
	void FlashBalls();
	void WriteDataFile();

// Dialog Data
	//{{AFX_DATA(CBallHiveDlg)
	enum { IDD = IDD_BALLHIVE_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBallHiveDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBallHiveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CExitBtn  m_ExitBtn;
	CAboutBtn m_AboutBtn;
	CLevelBtn m_BeginnerBtn;
	CLevelBtn m_ExpertBtn;
	CLevelBtn m_MasterBtn;
	CGameOver m_GameOver;
	CScore    m_Score;
	CHiScore  m_HiScore;
	CToolTipCtrl* m_pToolTips;

	void ReadDataFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BALLHIVEDLG_H__CC7A1762_ED54_4F0C_8EDA_AACFCAA65172__INCLUDED_)
