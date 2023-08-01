// BallPool.cpp: implementation of the CBallPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ballhive.h"
#include "BallPool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTakenBalls::CTakenBalls()
{

}

CTakenBalls::~CTakenBalls()
{
	// kill all balls
	std::list<CBall*>::iterator iter = m_Balls.begin();
	for(; iter != m_Balls.end(); )
	{
		CBall *pBall = *iter;
		++iter;
		pBall->DestroyWindow();
		delete pBall;
	}
}

void CTakenBalls::InsertBall(CBall *pBall)
{
	// insert a ball to taken list
	m_Balls.push_back(pBall);
}

bool CTakenBalls::FreeBall(CBall* pBall)
{
	// set a ball free
	std::list<CBall*>::iterator iter = m_Balls.begin();
	for(; iter != m_Balls.end(); ++iter)
	{
		if((*iter) == pBall)
		{
			m_Balls.remove(pBall);
			return true;
		}
	}
	return false;
}

void CTakenBalls::FlashBalls(bool bFlash)
{
	// look for flashing balls
	std::list<CBall*>::iterator iter = m_Balls.begin();
	for(; iter != m_Balls.end(); ++iter)
	{
		CBall *pBall = (*iter);

		// need to flash
		if(bFlash)
		{
			// hey ball! are you flashing?
			if(pBall->IsFlashing())
			{
				pBall->InverseFlash(); // change color
				pBall->Flash(true);   // draw yourself!
			}
		}
		else
		{
			// stop flashing!
			pBall->Flash(false);
		}
	}
}



///////////////////////////////////////////////////////////////////
CFreeBalls::CFreeBalls()
{

}

CFreeBalls::~CFreeBalls()
{
	// kill all balls
	std::list<CBall*>::iterator iter = m_Balls.begin();
	for(; iter != m_Balls.end(); )
	{
		CBall *pBall = *iter;
		++iter;
		pBall->DestroyWindow();
		delete pBall;
	}
}


CBall* CFreeBalls::GetBall()
{
	// get a free ball
	CBall *pBall = NULL;
	if(m_Balls.size())
	{
		pBall= m_Balls.front();
		m_Balls.pop_front();
	}
	return pBall;
}


void CFreeBalls::InsertBall(CBall *pBall)
{
	// insert a free ball to the list
	m_Balls.push_back(pBall);
}


///////////////////////////////////////////////////////////////////
CBallPool::CBallPool()
{
}

void CBallPool::Init(CWnd *pWnd, int id)
{
	// create 61 (free and hidden) balls
	for(int i = 0; i < 61; i++)
	{
		RECT rect = {0,0,25,25};
		CBall *pBall = new CBall;
		pBall->Create(NULL, "BALL", WS_CHILD | WS_VISIBLE | SS_NOTIFY, rect, pWnd, id++);
		pBall->ShowWindow(SW_HIDE);
		m_FreeBalls.InsertBall(pBall);
	}
}

CBallPool::~CBallPool()
{

}


CBall* CBallPool::GetFreeBall()
{
	// get a free ball ...
	CBall *pBall = m_FreeBalls.GetBall();
	if(pBall)
	{
		// ... and put it in the taken list!
		m_TakenBalls.InsertBall(pBall);
	}

	return pBall;
}

void CBallPool::SetBallFree(CBall* pBall)
{
	// is the ball taken ? (free it)
	if(m_TakenBalls.FreeBall(pBall))
	{
		// put it in the free list
		m_FreeBalls.InsertBall(pBall);
	}
	
	// and hide it
	pBall->ShowWindow(SW_HIDE);
}


void CBallPool::FlashBalls(bool bFlash)
{
	// flash balls
	m_TakenBalls.FlashBalls(bFlash);
}
