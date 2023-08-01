// BallHive.h : main header file for the BALLHIVE application
//

#if !defined(AFX_BALLHIVE_H__DDCE1634_DB1E_40C3_BAE3_31871ED1EC6C__INCLUDED_)
#define AFX_BALLHIVE_H__DDCE1634_DB1E_40C3_BAE3_31871ED1EC6C__INCLUDED_

#include "HiveGame.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBallHiveApp:
// See BallHive.cpp for the implementation of this class
//

#define CELL_WIDTH   34
#define CELL_HEIGHT  36
#define BOARD_WIDTH  390
#define BOARD_HEIGHT 350


class CBallHiveApp : public CWinApp
{
public:
	CBallHiveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBallHiveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	CHiveGame* GetGame() { return &m_TheGame; } // get the game obj

	//{{AFX_MSG(CBallHiveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CHiveGame m_TheGame;
	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BALLHIVE_H__DDCE1634_DB1E_40C3_BAE3_31871ED1EC6C__INCLUDED_)
