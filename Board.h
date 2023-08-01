// Board.h: interface for the CBoard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOARD_H__B69C3BB4_BEBB_4E48_8921_9420759AA9DE__INCLUDED_)
#define AFX_BOARD_H__B69C3BB4_BEBB_4E48_8921_9420759AA9DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


extern int g_cellsInLine[9];

class CBoard : public CStatic
{
// Construction
public:
	CBoard();

// Attributes
public:

// Operations
public:
	void Draw(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoard)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBoard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBoard)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_BOARD_H__B69C3BB4_BEBB_4E48_8921_9420759AA9DE__INCLUDED_)
