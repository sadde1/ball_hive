#if !defined(AFX_SCORE_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
#define AFX_SCORE_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Score.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScore window

class CScore : public CStatic
{
	int m_Score;
	int m_Color;

// Construction
public:
	CScore();

// Attributes
public:

// Operations
public:
	void SetScore(int score, bool add);
	void Draw(CDC *pDC);
	void Color(bool bFirst);
	int  GetScore() { return m_Score; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScore)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScore();

	// Generated message map functions
protected:
	//{{AFX_MSG(CScore)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORE_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
