#if !defined(AFX_HISCORE_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
#define AFX_HISCORE_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HiScore.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHiScore window

class CHiScore : public CStatic
{
	int m_HiScore;

// Construction
public:
	CHiScore();

// Attributes
public:

// Operations
public:
	void SetHiScore(int score);
	void Draw(CDC *pDC);
	int  GetHiScore();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHiScore)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHiScore();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHiScore)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISCORE_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
