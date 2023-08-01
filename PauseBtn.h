#if !defined(AFX_PAUSEBTN_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
#define AFX_PAUSEBTN_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PauseBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPauseBtn window
class CAboutDialog;

class CPauseBtn : public CStatic
{
	bool m_bPause;
	CAboutDialog *m_pDialog;
// Construction
public:
	CPauseBtn();

// Attributes
public:

// Operations
public:
	void Draw(CDC *pDC);
	void SetDialog(CAboutDialog *pDialog);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPauseBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPauseBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPauseBtn)
	afx_msg void OnClicked();
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAUSEBTN_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
