#if !defined(AFX_LEVELBTN_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
#define AFX_LEVELBTN_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LevelBtn.h : header file
//


typedef enum
{
	NO_LEVEL = -1,
	BEGINNER = 0,
	EXPERT,
	MASTER
} ELevels;

/////////////////////////////////////////////////////////////////////////////
// CLevelBtn window

class CLevelBtn : public CStatic
{
	ELevels m_Level;
	bool    m_bSelected;
// Construction
public:
	CLevelBtn(ELevels level);

// Attributes
public:

// Operations
public:
	void Select(bool Selected);
	void Draw(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevelBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLevelBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLevelBtn)
	afx_msg void OnClicked();
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVELBTN_H__F5902E80_CC62_4650_AB89_7E18E8EB7EE4__INCLUDED_)
