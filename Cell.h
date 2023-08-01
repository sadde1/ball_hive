// Cell.h: interface for the CCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__ED6042E9_E93E_4498_9F9D_50004942189A__INCLUDED_)
#define AFX_CELL_H__ED6042E9_E93E_4498_9F9D_50004942189A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ball.h"


class CHiveGame;


class CCell : public CWnd
{
	int    m_line;
	int    m_indexInLine;
	int    m_index;
	CBall *m_pBall;
	bool   m_bSelected;
	static CHiveGame* m_pTheGame;

// Construction
public:
	CCell();

// Attributes
public:
	static void SetGame(CHiveGame* pTheGame) {m_pTheGame = pTheGame; }
// Operations
public:
	void Draw(CDC *pDC);
	bool IsEmpty()         { return m_pBall == NULL; }

	int  GetIndex()        { return m_index; }
	int  GetLine()         { return m_line; }
	int  GetIndexInLine()  { return m_indexInLine; }
	void GetPos(int &line, int &indexInLine, int &index) { line = m_line; indexInLine = m_indexInLine; index = m_index; }
	void SetPos(int line, int indexInLine, int index) { m_line = line; m_indexInLine = indexInLine; m_index = index; }

	CBall *SetBall(CBall *pBall, bool bNewBall);
	CBall *GetBall() { return m_pBall; }

	void Select(bool bSelect) { m_bSelected = bSelect; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCell)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCell();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCell)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_CELL_H__ED6042E9_E93E_4498_9F9D_50004942189A__INCLUDED_)
