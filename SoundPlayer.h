// SoundPlayer.h: interface for the CSoundPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDPLAYER_H__DC360956_62D5_4A21_931F_F32ACAEC1123__INCLUDED_)
#define AFX_SOUNDPLAYER_H__DC360956_62D5_4A21_931F_F32ACAEC1123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mmsystem.h"


class CSoundPlayer  
{
public:
	CSoundPlayer();
	virtual ~CSoundPlayer();

	bool Play(LPTSTR lpName, HINSTANCE hInst, bool bSync);
};

#endif // !defined(AFX_SOUNDPLAYER_H__DC360956_62D5_4A21_931F_F32ACAEC1123__INCLUDED_)
