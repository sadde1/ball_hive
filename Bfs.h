// Bfs.h: interface for the CBfs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BFS_H__1DF4E258_079C_4520_A7F6_61F59ED72421__INCLUDED_)
#define AFX_BFS_H__1DF4E258_079C_4520_A7F6_61F59ED72421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <list>


class CCell;


class CNode
{
	CCell *m_Cell;
	int    m_d;
	CNode *m_p;
public:
	CNode(CCell *pCell);
	virtual ~CNode() {}

	void Set_d(int d) { m_d = d; }
	int  Get_d() { return m_d; }

	CNode *Get_p() { return m_p; }
	void   Set_p(CNode *p) { m_p = p; }

	CCell *GetCell() { return m_Cell; }
};


class CArc
{
	CNode* m_From;
	CNode* m_To;
	// lenght = 1 !!!!
public:
	CArc(CNode* from, CNode* to);
	virtual ~CArc() {}

	CNode* GetFrom() { return m_From; }
	CNode* GetTo()   { return m_To;   }
};


typedef std::vector<CNode*> N;
typedef std::vector<CArc*>  A;

class CGraph
{
	N m_Nodes;
	A m_Arcs;
public:
	CGraph(N n, A a) : m_Nodes(n), m_Arcs(a) {}

	virtual ~CGraph();

	N& V_G() { return m_Nodes; };
	A& GetArcs()  { return m_Arcs;  };
};


class CBfs
{
public:
	CBfs(CGraph* pG, CNode *p_s, CNode *p_t);
	virtual ~CBfs();

	void GetShortestPath(std::list<CNode*> &path);
	
private:
	std::list<CNode*> m_Q;
	CGraph *m_G;
	CNode*  m_s; 
	CNode*  m_t; 

	void Do();
	void Step(CNode *u);
};


#endif // !defined(AFX_BFS_H__1DF4E258_079C_4520_A7F6_61F59ED72421__INCLUDED_)
