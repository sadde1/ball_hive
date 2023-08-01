// Bfs.cpp: implementation of the CBfs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ballhive.h"
#include "Bfs.h"
#include "Cell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNode::CNode(CCell *pCell) 
{
	m_Cell  = pCell;   // node is actually a cell. this cell
	m_d     = INT_MAX; // distance init to max
	m_p     = NULL;    // no previous!
}



CArc::CArc(CNode* from, CNode* to) 
{
	m_From = from;
	m_To   = to;
}


CGraph::~CGraph() 
{
	// kill all arcs
	A::iterator iterArcs = m_Arcs.begin();
	for(; iterArcs != m_Arcs.end(); )
	{
		CArc *pArc = *iterArcs;
		iterArcs++;
		delete pArc;
	}
}




CBfs::~CBfs()
{
	// delete the graph
	if(m_G != NULL)
		delete m_G;
}

CBfs::CBfs(CGraph* pG, CNode *p_s, CNode* p_t)
{
	m_G = pG;  // set graph
	m_s = p_s; // set start node
	m_t = p_t; // set target node
	
	Do();      // BFS, Do you stuff!
}



void CBfs::Do()
{
	m_Q.clear(); // clear the Q

	// for each node in G
	for(int i = 0; i < (int)m_G->V_G().size(); i++)
	{
		m_G->V_G()[i]->Set_d(-1);   // set distance to -1
		m_G->V_G()[i]->Set_p(NULL); // set no previous 
	}

	m_s->Set_d(0); // distance from start is 0

	m_Q.push_back(m_s); // push start to QS

	// while Q is not empty AND distance of target is -1
	while(m_Q.size() && (m_t->Get_d() == -1))
	{
		// take out first node u from Q
		CNode *u = m_Q.front(); 
		m_Q.remove(u);

		// Step from u
		Step(u);
	}

}


void CBfs::Step(CNode *u)
{
	// for each arc:  u -- v do: 
		// if distance(v) == -1 do:
			// distance(v) <- distance(u)+1
			// put v in Q

	// for each arc
	for(int i = 0; i < (int)m_G->GetArcs().size(); i++)
	{
		CNode *v = NULL;
		// find v: (arc from u)

		// from u?
		if(m_G->GetArcs()[i]->GetFrom() == u)
		{
			// this is v !!
			v = m_G->GetArcs()[i]->GetTo();
		}
		// to u?
		else if(m_G->GetArcs()[i]->GetTo() == u)
		{
			// this is v !!
			v = m_G->GetArcs()[i]->GetFrom();
		}

		// v OK?
		if(v == NULL)
			continue;

		// distance(v) is not -1
		if(v->Get_d() != -1)
			continue;

		// distance(v) <- distance(u)+1
		v->Set_d(u->Get_d() + 1);

		// set u as previous of v.  (scheame for finding the path)
		v->Set_p(u);

		// // put v in Q
		m_Q.push_back(v);
	}
}

void CBfs::GetShortestPath(std::list<CNode*> &path)
{
	CNode *pCurr = m_t;

	// go from target to start (throu previous)
	do
	{
		path.push_front(pCurr);
		pCurr = pCurr->Get_p();
	} while(pCurr);
}
