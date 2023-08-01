#if !defined(AFX_ABOUTDIALOG_H__FFF9521A_067B_414B_AE64_EC296905FBEC__INCLUDED_)
#define AFX_ABOUTDIALOG_H__FFF9521A_067B_414B_AE64_EC296905FBEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDialog.h : header file
//

#include "OkBtn.h"	// Added by ClassView
#include "ShowBtn.h"	// Added by ClassView
#include "AboutFgr.h"
#include "PauseBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

class CAboutDialog : public CDialog
{
	CPoint    m_MovePnt;        // move the dialog to
	bool      m_bMoveDlg;       // move the dialog
	CRgn      m_rgn;            // region of the dialog (not a rect!)
	COkBtn    m_OkBtn;
	CShowBtn  m_ShowBtn;
	UINT      m_PaintTimer;
	CAboutFgr m_Fgr;
	CPauseBtn m_PauseBtn;
// Construction
public:
	CAboutDialog(CWnd* pParent = NULL);   // standard constructor
	void OK();
	void Pause(bool bPause);

// Dialog Data
	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_DIALOG_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	static bool m_bOpenOnStartup;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	CToolTipCtrl* m_pToolTips;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDIALOG_H__FFF9521A_067B_414B_AE64_EC296905FBEC__INCLUDED_)
