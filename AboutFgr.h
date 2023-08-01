// AboutFgr.h: interface for the CAboutFgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUT_FGR_H__B69C3BB4_BEBB_4E48_8921_9420759AA9DE__INCLUDED_)
#define AFX_ABOUT_FGR_H__B69C3BB4_BEBB_4E48_8921_9420759AA9DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 

class CAboutFgr : public CStatic
{
	int m_Y;
// Construction
public:
	CAboutFgr();

// Attributes
public:

// Operations
public:
	void Draw(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutFgr)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAboutFgr();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAboutFgr)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_ABOUT_FGR_H__B69C3BB4_BEBB_4E48_8921_9420759AA9DE__INCLUDED_)
