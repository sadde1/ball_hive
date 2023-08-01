// HiveGame.h: interface for the CHiveGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIVEGAME_H__7BFC0C06_821E_4765_9E52_5F53D2F756AA__INCLUDED_)
#define AFX_HIVEGAME_H__7BFC0C06_821E_4765_9E52_5F53D2F756AA__INCLUDED_

#include "Board.h"
#include "Cell.h"
#include "LevelBtn.h"
#include "BallPool.h"
#include <stack>
#include <list>
#include "Bfs.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef enum
{
	NORTH_EAST = 0,
	EAST,
	SOUTH_EAST,
	SOUTH_WEST,
	WEST, 
	NORTH_WEST,

	NUM_OF_DIRECTIONS
} EDirection;


class CBallHiveDlg;


class CHiveGame  
{
	CBoard        m_Board;
	CCell         m_Cells[61];
	CNode        *m_Nodes[61];
	CBallHiveDlg *m_pBallHiveDlg;
	CBallPool     m_BallPool;
	bool          m_CalcCells[61];
	bool          m_GameOver;
	ELevels       m_Level;

	CCell         *m_pSelectedCell;
	CNode         *m_pTargetNode;
 
	std::list<CNode*> m_ShortestPath;

	int  GetNeighbor(int cellIndex, EDirection direction, bool bLookForBall, EBallColor color=NUM_OF_BALL_COLORS);

	bool FindPath(CCell *m_pSelectedCell, CCell *pCell);
	bool GetGraph(N& n, A& a, CCell *pSource, CCell *pTarget);
	void RecFindNodes(CNode* pNode, CCell* pTarget, N& n, A& a);

	bool CheckPatterns(EBallColor color);

	bool CheckForPattren256(std::list<int> &AllCells);
	bool CheckForPattren128(std::list<int> &AllCells);
	bool CheckForPattren64(std::list<int> &AllCells);
	bool CheckForPattren32(std::list<int> &AllCells);
	bool CheckForPattren16(std::list<int> &AllCells);
	bool CheckForPattren8(std::list<int> &AllCells);
	bool CheckForPattren4(std::list<int> &AllCells);
	bool CheckForPattren2_a(std::list<int> &AllCells);
	bool CheckForPattren2_b(std::list<int> &AllCells);
	bool CheckForPattren2_c(std::list<int> &AllCells);

	bool CheckForLinePattren(std::list<int> &AllCells, int numOfCells, EDirection direction);
	bool CheckForHexagonPattren(std::list<int> &AllCells, bool bMiddle);

	bool AddBalls();
	void GameOver();

public:
	CHiveGame();
	virtual ~CHiveGame();

	void Init();
	void Restart(ELevels level);

	void Select(CCell *pCell);
	CCell *GetCell(int index) { return &m_Cells[index]; }

	void Moved();

	CBallHiveDlg *GetBallHiveDlg() { return m_pBallHiveDlg; }
	void SetBallHiveDlg(CBallHiveDlg *pBallHiveDlg) { m_pBallHiveDlg = pBallHiveDlg; }
	void FlashBalls(bool bFlash);
};

#endif // !defined(AFX_HIVEGAME_H__7BFC0C06_821E_4765_9E52_5F53D2F756AA__INCLUDED_)
