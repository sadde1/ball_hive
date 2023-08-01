#if !defined(AFX_GAMEOVER_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
#define AFX_GAMEOVER_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameOver.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameOver window

class CGameOver : public CStatic
{
// Construction
public:
	CGameOver();

// Attributes
public:

// Operations
public:
	void Draw(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameOver)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGameOver();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGameOver)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEOVER_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
