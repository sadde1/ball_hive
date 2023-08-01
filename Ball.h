#if !defined(AFX_BALL_H__F6956DED_2456_4F03_8E59_7D86E4C5F7BB__INCLUDED_)
#define AFX_BALL_H__F6956DED_2456_4F03_8E59_7D86E4C5F7BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ball.h : header file
//


// possible colors of balls
typedef enum {
	RED_BALL = 0,
	GREEN_BALL,
	DARK_BLUE_BALL,
	LIGHT_BLUE_BALL,
	BROWN_BALL,
	ORANGE_BALL,
	PINK_BALL,
	GRAY_BALL,

	NUM_OF_BALL_COLORS
} EBallColor;


class CCell;

// CBall - represent a ball
class CBall : public CWnd
{
	CCell      *m_pCell; // in which cell the ball is in
	EBallColor  m_color; // color of the ball
	int m_X;             // where to draw the ball (x in the window coords)
	int m_Y;             // where to draw the ball (y in the window coords)

	bool m_bFlash;
	bool m_bRegularColor;

public:
	CBall();
	virtual ~CBall();

	EBallColor GetColor() { return m_color; }
	void SetColor(EBallColor color) { m_color = color; }

	void Draw(CDC *pDC);          // draw the ball to screen
	void SetCell(CCell *pCell);   // locate the ball in a cell

	void Flash(bool bFlash);
	void InverseFlash() { m_bRegularColor = !m_bRegularColor; } 
	bool IsFlashing() { return m_bFlash; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBall)
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	//{{AFX_MSG(CBall)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BALL_H__F6956DED_2456_4F03_8E59_7D86E4C5F7BB__INCLUDED_)
