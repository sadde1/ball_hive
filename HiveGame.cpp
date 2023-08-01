// HiveGame.cpp: implementation of the CHiveGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BallHive.h"
#include "HiveGame.h"
#include "BallHiveDlg.h"
#include "Mmsystem.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static long g_ID = 0xf000;
extern CBallHiveApp theApp;

// directions (of neibours and moves)
char *DIR[6] = {"NORTH_EAST", "EAST", "SOUTH_EAST", "SOUTH_WEST", "WEST", "NORTH_WEST"};
	 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHiveGame::CHiveGame()
{
	CCell::SetGame(this); // let the cell class know the game
	m_pSelectedCell = NULL;
	m_GameOver      = false;
}

CHiveGame::~CHiveGame()
{
	// kill all nodes
	for(int i = 0; i < 61; i++)
		delete m_Nodes[i];
}

void CHiveGame::Init()
{
	RECT rect;

	// build the board
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = BOARD_WIDTH+25;
	rect.bottom = BOARD_HEIGHT+25;
	m_Board.Create(NULL, WS_CHILD | WS_VISIBLE, rect, (CWnd*)m_pBallHiveDlg);

	int cellIndex = 0;
	// 9 lines
	for(int line = 0; line < 9; line++)
	{
		// for each cell in the line:
		for(int cell = 0; cell < g_cellsInLine[line]; cell++)
		{
			// build the cell
			rect.left   = BOARD_WIDTH/2+ cell*CELL_WIDTH - g_cellsInLine[line]*CELL_HEIGHT/2 - 20, 
			rect.top    = (BOARD_HEIGHT - 7 * CELL_HEIGHT)/2 + line*28 - 10;
			rect.right  = rect.left + CELL_WIDTH+1;
			rect.bottom = rect.top + CELL_HEIGHT+1;

			m_Cells[cellIndex].Create(NULL, "CELL", WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, (CWnd*)m_pBallHiveDlg, ++g_ID);
			m_Cells[cellIndex].SetPos(line, cell, cellIndex);

			CRgn rgn;
			POINT points[7] = { {18,0}, {35,7}, {35,29}, {17,37}, {0,29}, {0,7}, {17,0} };
			rgn.CreatePolygonRgn(points, 7, WINDING);
			m_Cells[cellIndex].SetWindowRgn(rgn, true);
			m_Cells[cellIndex].ShowWindow(SW_SHOW);

			// cell is also a node in the BFS
			m_Nodes[cellIndex] = new CNode(&m_Cells[cellIndex]);

			cellIndex++;
		}
	}

	// init the ball pool
	m_BallPool.Init((CWnd*)m_pBallHiveDlg, ++g_ID);

	// play start sound
	m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_CELL, theApp.m_hInstance, false);
	g_ID += 61;
}



void CHiveGame::Select(CCell *pCell)
{
	if(m_GameOver)
		return;

	if(m_pBallHiveDlg->IsMoving())
		return;

	bool bSelect   = false;
	bool bUnSelect = false;
	bool bMove     = false;
	
	// select a ball ?
	if(!m_pSelectedCell && pCell->GetBall())
	{
		bSelect = true;
	}
	else if(m_pSelectedCell == pCell) // unselect a ball
	{
		bUnSelect = true;
	}
	else if(m_pSelectedCell && !pCell->GetBall()) // move a ball
	{
		if(FindPath(m_pSelectedCell, pCell))
		{
			bMove     = true;
			bUnSelect = true;
		}
		else
			m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_ERROR, theApp.m_hInstance, false);
	}

	// Move ball
	if(bMove)
	{
		m_pBallHiveDlg->MoveBall(m_ShortestPath);
		m_ShortestPath.clear();
	}

	// Unselect ball
	if(bUnSelect)
	{
		m_pSelectedCell->Select(false);
		m_pSelectedCell->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		if(m_pSelectedCell->GetBall())
			m_pSelectedCell->GetBall()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		m_pSelectedCell = NULL;
	}

	// Select ball
	if(bSelect)
	{
		m_pSelectedCell = pCell;
		m_pSelectedCell->Select(true);
		m_pSelectedCell->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		if(m_pSelectedCell->GetBall())
			m_pSelectedCell->GetBall()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}


void CHiveGame::Restart(ELevels level)
{
	// init game
	m_GameOver = false;
	m_pBallHiveDlg->Score(0, false);
	m_pBallHiveDlg->GameOver(false);
	m_Level = level;

	// how many balls to start with
	int startBalls = 10 * (m_Level+1);

	// set level
	m_pBallHiveDlg->Level(m_Level);

	// init balls
	for(int i = 0; i < 61; i++)
	{
		if(m_Cells[i].GetBall())
		{
			m_BallPool.SetBallFree(m_Cells[i].GetBall());
		}
		m_Cells[i].SetBall(NULL, false);
	}
	
	// unselect cell
	if(m_pSelectedCell)
	{
		m_pSelectedCell->Select(false);
		m_pSelectedCell->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
	m_pSelectedCell = NULL;


	// put balls (random place and color)
	for(int i = 0; i < startBalls; i++)
	{
		CBall *pBall = m_BallPool.GetFreeBall();
		pBall->SetColor((EBallColor)(rand() % 8));
		
		int cell;
		do
		{
			cell = rand() % 61;
		} while (!m_Cells[cell].IsEmpty());
		m_Cells[cell].SetBall(pBall, false);
	}
}



bool CHiveGame::FindPath(CCell *m_pSelectedCell, CCell *pCell)
{
	CGraph *pGraph;
	N n;
	A a;

	// is ther a graph from source to target?
	if(!GetGraph(n, a, m_pSelectedCell, pCell))
	{
		// no! delete the arcs!
		A::iterator iterArcs = a.begin();
		for(; iterArcs != a.end(); )
		{
			CArc *pArc = *iterArcs;
			iterArcs++;
			delete pArc;
		}

		return false;
	}
	
	// create a graph
	pGraph = new CGraph(n, a);

	// do BFS
	CBfs b(pGraph, n[0], m_pTargetNode);

	// get the shortest path
	b.GetShortestPath(m_ShortestPath);
	
	// is there a path?
	return m_ShortestPath.size() ? true : false;

}




int CHiveGame::GetNeighbor(int cellIndex, EDirection direction, bool bLookForBall, EBallColor color)
{
	int line = -1;
	int indexInLine = cellIndex;
	int copyCell    = cellIndex;

	while(copyCell >= 0)
	{
		line++;
		copyCell -= g_cellsInLine[line];
		if(copyCell >= 0)
			indexInLine = copyCell;
	}

	int Neighbor = cellIndex;
	int NeighborLine = line;
	if((direction == NORTH_EAST) || (direction == NORTH_WEST))
		NeighborLine--;
	if((direction == SOUTH_EAST) || (direction == SOUTH_WEST))
		NeighborLine++;

	switch(direction)
	{
	case NORTH_EAST:
		if(line == 0)
			return -1;

		Neighbor -= g_cellsInLine[NeighborLine];
		if(g_cellsInLine[line] < g_cellsInLine[NeighborLine])
			Neighbor++;
		break;

	case EAST:
		Neighbor++;
		break;

	case SOUTH_EAST:
		if(line == 8)
			return -1;

		Neighbor += g_cellsInLine[NeighborLine];
		if(g_cellsInLine[line] > g_cellsInLine[NeighborLine])
			Neighbor++;
		break;

	case SOUTH_WEST:
		if(line == 8)
			return -1;

		Neighbor += g_cellsInLine[NeighborLine];
		if(g_cellsInLine[line] < g_cellsInLine[NeighborLine])
			Neighbor--;
		break;

	case WEST:
		Neighbor--;
		break;

	case NORTH_WEST:
		if(line == 0)
			return -1;

		Neighbor -= g_cellsInLine[NeighborLine];
		if(g_cellsInLine[line] > g_cellsInLine[NeighborLine])
			Neighbor--;
		break;
	}


	int NeighborMin = 0;
	int NeighborMax = 4;
	for(int i = 1; i <= NeighborLine; i++)
	{
		NeighborMin += g_cellsInLine[i-1];
		NeighborMax += g_cellsInLine[i];
	}
	if((Neighbor < NeighborMin) || (Neighbor > NeighborMax))
		Neighbor = -1;

	if(!bLookForBall)
	{
		if(!m_Cells[Neighbor].IsEmpty())
			Neighbor = -1;
	}
	else
	{
		if(m_Cells[Neighbor].IsEmpty())
			Neighbor = -1;
		else
		{
			if(color == NUM_OF_BALL_COLORS)
				return Neighbor;
			if(m_Cells[Neighbor].GetBall()->GetColor() != color)
				Neighbor = -1;
		}
	}

	return Neighbor;
}



bool CHiveGame::GetGraph(N& n, A& a, CCell *pSource, CCell *pTarget)
{
	// init all cells
	for(int i = 0; i < 61; i++)
		m_CalcCells[i] = false;

	m_pTargetNode = NULL;

	// start node
	CNode *pSourceNode = m_Nodes[m_pSelectedCell->GetIndex()];
	
	// remove the ball from source (only for finding the graph) (*)
	CBall *pBall = pSource->SetBall(NULL, false);

	// find all nodes making a graph from source to target
	RecFindNodes(pSourceNode, pTarget, n, a);

	// return the ball (*)
	pSource->SetBall(pBall, false);


	// got to target ?
	return m_pTargetNode ? true : false;
}


void CHiveGame::RecFindNodes(CNode* pNode, CCell* pTarget, N& n, A& a)
{
	if(!pNode->GetCell()->IsEmpty())
		return;

	int cell = pNode->GetCell()->GetIndex();
	if(m_CalcCells[cell])
		return;
	
	n.push_back(pNode);

	int Neighbor;
	std::vector<CNode*> Neighbors;

	for(int i = NORTH_EAST; i < NUM_OF_DIRECTIONS; i++)
	{
		if((Neighbor = GetNeighbor(cell, (EDirection)i, false)) != -1)
		{
			if(!m_CalcCells[Neighbor])
			{
				CNode *pNeighbor = m_Nodes[Neighbor];
				a.push_back(new CArc(pNode, pNeighbor));
				Neighbors.push_back(pNeighbor);
				
				// remember the target node
				if(pTarget == &m_Cells[Neighbor])
					m_pTargetNode = pNeighbor;
			}
		}
	}
	m_CalcCells[cell] = true;
	for(int i = 0; i < (int)Neighbors.size(); i++)
	{
		RecFindNodes(Neighbors[i], pTarget, n, a);
	}
}


void CHiveGame::Moved()
{
	bool bRemoved = false; 

	for(int i = 0; i < NUM_OF_BALL_COLORS; i++)
		bRemoved |= CheckPatterns((EBallColor)i);

	if(!bRemoved)
	{
		AddBalls();
	}
}

bool CHiveGame::CheckPatterns(EBallColor color)
{
	std::list<int> AllCells;
	for(int i = 0; i < 61; i++)
	{
		if(m_Cells[i].GetBall() != NULL)
		{
			if(m_Cells[i].GetBall()->GetColor() == color)
				AllCells.push_back(m_Cells[i].GetIndex());
		}
	}

	bool bRemoved = false; 

	// important: the cells inserted from to to bottom, left to right!!

	while(AllCells.size())
	{
		if(CheckForPattren256(AllCells))
		{
			bRemoved = true;
			m_pBallHiveDlg->Score(256, true);
			continue;
		}
		if(CheckForPattren128(AllCells))
		{
			m_pBallHiveDlg->Score(128, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren64(AllCells))
		{
			m_pBallHiveDlg->Score(64, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren32(AllCells))
		{
			m_pBallHiveDlg->Score(32, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren16(AllCells))
		{
			m_pBallHiveDlg->Score(16, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren8(AllCells))
		{
			m_pBallHiveDlg->Score(8, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren4(AllCells))
		{
			m_pBallHiveDlg->Score(4, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren2_a(AllCells))
		{
			m_pBallHiveDlg->Score(2, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren2_b(AllCells))
		{
			m_pBallHiveDlg->Score(2, true);
			bRemoved = true;
			continue;
		}
		if(CheckForPattren2_c(AllCells))
		{
			m_pBallHiveDlg->Score(2, true);
			bRemoved = true;
			continue;
		}
		
		AllCells.pop_front();
	}

	return bRemoved;
}



bool CHiveGame::CheckForPattren256(std::list<int> &AllCells)
{
	if(CheckForLinePattren(AllCells, 9, EAST) || 
		CheckForLinePattren(AllCells, 9, SOUTH_WEST) || 
		CheckForLinePattren(AllCells, 9, SOUTH_EAST))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_256, theApp.m_hInstance, false);
		return true;
	}

	return false;
}


bool CHiveGame::CheckForPattren128(std::list<int> &AllCells)
{
	if(CheckForLinePattren(AllCells, 8, EAST) || 
		CheckForLinePattren(AllCells, 8, SOUTH_WEST) || 
		CheckForLinePattren(AllCells, 8, SOUTH_EAST))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_128, theApp.m_hInstance, false);
		return true;
	}

	return false;
}

bool CHiveGame::CheckForPattren64(std::list<int> &AllCells)
{
	if(CheckForLinePattren(AllCells, 7, EAST) || 
		CheckForLinePattren(AllCells, 7, SOUTH_WEST) || 
		CheckForLinePattren(AllCells, 7, SOUTH_EAST))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_64, theApp.m_hInstance, false);
		return true;
	}

	return false;
}

bool CHiveGame::CheckForPattren32(std::list<int> &AllCells)
{
	if(CheckForHexagonPattren(AllCells, true))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_32, theApp.m_hInstance, false);

		return true;
	}

	return false;
}

bool CHiveGame::CheckForPattren16(std::list<int> &AllCells)
{
	if(CheckForLinePattren(AllCells, 6, EAST) || 
		CheckForLinePattren(AllCells, 6, SOUTH_WEST) || 
		CheckForLinePattren(AllCells, 6, SOUTH_EAST))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_16, theApp.m_hInstance, false);
		return true;
	}

	return false;
}

bool CHiveGame::CheckForPattren8(std::list<int> &AllCells)
{
	if(CheckForHexagonPattren(AllCells, false))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_8, theApp.m_hInstance, false);
		return true;
	}
	
	return false;
}

bool CHiveGame::CheckForPattren4(std::list<int> &AllCells)
{
	if(CheckForLinePattren(AllCells, 5, EAST) || 
		CheckForLinePattren(AllCells, 5, SOUTH_WEST) || 
		CheckForLinePattren(AllCells, 5, SOUTH_EAST))
	{
		m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_4, theApp.m_hInstance, false);
		return true;
	}

	return false;
}



bool CHiveGame::CheckForPattren2_a(std::list<int> &AllCells)
{
	//     ()
	//    ()()
	//     ()

	int n_sw, n_se, n_ss;
	EBallColor color = m_Cells[AllCells.front()].GetBall()->GetColor();
	if((n_sw = GetNeighbor(AllCells.front(), SOUTH_WEST, true, color)) != -1)
	{
		if((n_se = GetNeighbor(AllCells.front(), SOUTH_EAST, true, color)) != -1)
		{
			if((n_ss = GetNeighbor(n_sw, SOUTH_EAST, true, color)) != -1)
			{
			
				m_BallPool.SetBallFree(m_Cells[AllCells.front()].GetBall());
				m_Cells[AllCells.front()].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_sw].GetBall());
				m_Cells[n_sw].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_se].GetBall());
				m_Cells[n_se].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_ss].GetBall());
				m_Cells[n_ss].SetBall(NULL, false);


				AllCells.pop_front();
				AllCells.remove(n_se);
				AllCells.remove(n_sw);
				AllCells.remove(n_ss);

				m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_2, theApp.m_hInstance, false);
				
				return true;
			}
		}
	}
	return false;
}

bool CHiveGame::CheckForPattren2_b(std::list<int> &AllCells)
{
	//       ()
	//    ()() 
	//       ()

	int n_sw, n_se, n_ss, n_sww, n_see;
	EBallColor color = m_Cells[AllCells.front()].GetBall()->GetColor();
	if((n_sw = GetNeighbor(AllCells.front(), SOUTH_WEST, true, color)) != -1)
	{
		if((n_sww = GetNeighbor(n_sw, WEST, true, color)) != -1)
		{
			if((n_ss = GetNeighbor(n_sw, SOUTH_EAST, true, color)) != -1)
			{
			
				m_BallPool.SetBallFree(m_Cells[AllCells.front()].GetBall());
				m_Cells[AllCells.front()].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_sw].GetBall());
				m_Cells[n_sw].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_sww].GetBall());
				m_Cells[n_sww].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_ss].GetBall());
				m_Cells[n_ss].SetBall(NULL, false);


				AllCells.pop_front();
				AllCells.remove(n_sw);
				AllCells.remove(n_sww);
				AllCells.remove(n_ss);

				m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_2, theApp.m_hInstance, false);
				
				return true;
			}
		}
	}

	//    ()
	//     ()()
	//    ()
	if((n_se = GetNeighbor(AllCells.front(), SOUTH_EAST, true, color)) != -1)
	{
		if((n_see = GetNeighbor(n_se, EAST, true, color)) != -1)
		{
			if((n_ss = GetNeighbor(n_se, SOUTH_WEST, true, color)) != -1)
			{
			
				m_BallPool.SetBallFree(m_Cells[AllCells.front()].GetBall());
				m_Cells[AllCells.front()].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_se].GetBall());
				m_Cells[n_se].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_see].GetBall());
				m_Cells[n_see].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_ss].GetBall());
				m_Cells[n_ss].SetBall(NULL, false);


				AllCells.pop_front();
				AllCells.remove(n_se);
				AllCells.remove(n_see);
				AllCells.remove(n_ss);

				m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_2, theApp.m_hInstance, false);
				
				return true;
			}
		}
	}
	
	
	return false;
}

bool CHiveGame::CheckForPattren2_c(std::list<int> &AllCells)
{
	//     ()()
	//    ()() 

	int n_e, n_sw, n_se, n_see;
	EBallColor color = m_Cells[AllCells.front()].GetBall()->GetColor();
	if((n_e = GetNeighbor(AllCells.front(), EAST, true, color)) != -1)
	{
		if((n_sw = GetNeighbor(AllCells.front(), SOUTH_WEST, true, color)) != -1)
		{
			if((n_se = GetNeighbor(AllCells.front(), SOUTH_EAST, true, color)) != -1)
			{
			
				m_BallPool.SetBallFree(m_Cells[AllCells.front()].GetBall());
				m_Cells[AllCells.front()].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_e].GetBall());
				m_Cells[n_e].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_sw].GetBall());
				m_Cells[n_sw].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_se].GetBall());
				m_Cells[n_se].SetBall(NULL, false);


				AllCells.pop_front();
				AllCells.remove(n_e);
				AllCells.remove(n_sw);
				AllCells.remove(n_se);

				m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_2, theApp.m_hInstance, false);
				
				return true;
			}
		}
	}

	//   ()()
	//    ()() 
	if((n_e = GetNeighbor(AllCells.front(), EAST, true, color)) != -1)
	{
		if((n_se = GetNeighbor(AllCells.front(), SOUTH_EAST, true, color)) != -1)
		{
			if((n_see = GetNeighbor(n_se, EAST, true, color)) != -1)
			{
			
				m_BallPool.SetBallFree(m_Cells[AllCells.front()].GetBall());
				m_Cells[AllCells.front()].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_e].GetBall());
				m_Cells[n_e].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_se].GetBall());
				m_Cells[n_se].SetBall(NULL, false);
				m_BallPool.SetBallFree(m_Cells[n_see].GetBall());
				m_Cells[n_see].SetBall(NULL, false);


				AllCells.pop_front();
				AllCells.remove(n_e);
				AllCells.remove(n_se);
				AllCells.remove(n_see);

				m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_2, theApp.m_hInstance, false);
				
				return true;
			}
		}
	}
	
	
	return false;
}




bool CHiveGame::CheckForLinePattren(std::list<int> &AllCells, int numOfCells, EDirection direction)
{
	int n[9];
	EBallColor color = m_Cells[AllCells.front()].GetBall()->GetColor();

	n[0] = AllCells.front();
	for(int i = 1; i < numOfCells; i++)
	{
		if((n[i] = GetNeighbor(n[i-1], direction, true, color)) == -1)
			return false;
	}

	for(int i = 0; i < numOfCells; i++)
	{
		m_BallPool.SetBallFree(m_Cells[n[i]].GetBall());
		m_Cells[n[i]].SetBall(NULL, false);
	}

	for(int i = 0; i < numOfCells; i++)
	{
		AllCells.remove(n[i]);
	}

	return true;	
}


bool CHiveGame::CheckForHexagonPattren(std::list<int> &AllCells, bool bMiddle)
{
	//     (-)(1)
	//    (2)  (3) 
	//     (4)(5)


	int n_1, n_2, n_3, n_4, n_5, middle;
	EBallColor color = m_Cells[AllCells.front()].GetBall()->GetColor();
	if((n_1 = GetNeighbor(AllCells.front(), EAST, true, color)) != -1)
	{
		if((n_2 = GetNeighbor(AllCells.front(), SOUTH_WEST, true, color)) != -1)
		{
			if((n_3 = GetNeighbor(n_1, SOUTH_EAST, true, color)) != -1)
			{
				if((n_4 = GetNeighbor(n_2, SOUTH_EAST, true, color)) != -1)
				{
					if((n_5 = GetNeighbor(n_4, EAST, true, color)) != -1)
					{
						if(bMiddle)
						{
							if((middle = GetNeighbor(AllCells.front(), SOUTH_EAST, true, NUM_OF_BALL_COLORS)) == -1)
							{
								return false;
							}
						}
			
						m_BallPool.SetBallFree(m_Cells[AllCells.front()].GetBall());
						m_Cells[AllCells.front()].SetBall(NULL, false);
						m_BallPool.SetBallFree(m_Cells[n_1].GetBall());
						m_Cells[n_1].SetBall(NULL, false);
						m_BallPool.SetBallFree(m_Cells[n_2].GetBall());
						m_Cells[n_2].SetBall(NULL, false);
						m_BallPool.SetBallFree(m_Cells[n_3].GetBall());
						m_Cells[n_3].SetBall(NULL, false);
						m_BallPool.SetBallFree(m_Cells[n_4].GetBall());
						m_Cells[n_4].SetBall(NULL, false);
						m_BallPool.SetBallFree(m_Cells[n_5].GetBall());
						m_Cells[n_5].SetBall(NULL, false);
						if(bMiddle)
						{
							m_BallPool.SetBallFree(m_Cells[middle].GetBall());
							m_Cells[middle].SetBall(NULL, false);
						}

						AllCells.pop_front();
						AllCells.remove(n_1);
						AllCells.remove(n_2);
						AllCells.remove(n_3);
						AllCells.remove(n_4);
						AllCells.remove(n_5);
						if(bMiddle)
							AllCells.remove(middle);

						return true;
					}
				}
			}
		}
	}

	return false;
}


bool CHiveGame::AddBalls()
{
	int addBalls = 0;
	switch(m_Level)
	{
		case BEGINNER:
			addBalls = 3;
			if(m_BallPool.GetNumOfTakenBalls() > 24)
			{
				addBalls = 2;
			}
			if(m_BallPool.GetNumOfTakenBalls() > 40)
			{
				addBalls = 1;
			}
			break;

		case EXPERT:
			addBalls = 5;
			if(m_BallPool.GetNumOfTakenBalls() > 24)
			{
				addBalls = 3;
			}
			if(m_BallPool.GetNumOfTakenBalls() > 30)
			{
				addBalls = 2;
			}
			if(m_BallPool.GetNumOfTakenBalls() > 41)
			{
				addBalls = 1;
			}
			break;

		case MASTER:
			addBalls = 5;
			if(m_BallPool.GetNumOfTakenBalls() > 39)
			{
				addBalls = 3;
			}
			if(m_BallPool.GetNumOfTakenBalls() > 52)
			{
				addBalls = 1;
			}
			break;
	}

	while(addBalls)
	{
		CBall *pBall = NULL;
		if((pBall = m_BallPool.GetFreeBall()) == NULL)
		{
			// game over
			return false;
		}
		pBall->SetColor((EBallColor)(rand() % 8));
		
		int cell;
		do
		{
			cell = rand() % 61;
		} while (!m_Cells[cell].IsEmpty());
		m_Cells[cell].SetBall(pBall, true);

		addBalls--;
	}


	if(!m_BallPool.IsFreeBalls())
	{
		// game over
		GameOver();
		m_pBallHiveDlg->FlashBalls();
		return false;
	}

	m_pBallHiveDlg->FlashBalls();
	return true;
}


void CHiveGame::GameOver()
{
	m_pBallHiveDlg->m_SoundPlayer.Play((char*)IDR_WAVE_DEAD, theApp.m_hInstance, false);
	m_GameOver = true;
	m_pBallHiveDlg->GameOver(true);

}


void CHiveGame::FlashBalls(bool bFlash)
{
	m_BallPool.FlashBalls(bFlash);
}