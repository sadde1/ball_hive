// BallPool.h: interface for the CBallPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALLPOOL_H__FEE4CA0F_0630_487A_8DFD_FB4D2F762FFF__INCLUDED_)
#define AFX_BALLPOOL_H__FEE4CA0F_0630_487A_8DFD_FB4D2F762FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>

class CTakenBalls
{
	std::list<CBall*> m_Balls;
public:
	CTakenBalls();
	virtual ~CTakenBalls();
	int Size() { return m_Balls.size(); }

	void InsertBall(CBall *pBall);
	bool FreeBall(CBall* pBall);
	void FlashBalls(bool bFlash);


};

class CFreeBalls
{
	std::list<CBall*> m_Balls;
public:
	CFreeBalls();
	virtual ~CFreeBalls();
	int Size() { return m_Balls.size(); }

	CBall* GetBall();
	void InsertBall(CBall *pBall);
};


class CBallPool  
{
	CTakenBalls m_TakenBalls;
	CFreeBalls  m_FreeBalls;
public:
	CBallPool();
	virtual ~CBallPool();

	void    Init(CWnd *pWnd, int id);
	CBall*  GetFreeBall();
	void    SetBallFree(CBall* pBall);
	int     GetNumOfTakenBalls() { return m_TakenBalls.Size(); }
	void    FlashBalls(bool bFlash);

	bool IsFreeBalls() { return m_FreeBalls.Size() ? true : false; }

};

#endif // !defined(AFX_BALLPOOL_H__FEE4CA0F_0630_487A_8DFD_FB4D2F762FFF__INCLUDED_)
