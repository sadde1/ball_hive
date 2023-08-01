// SoundPlayer.cpp: implementation of the CSoundPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ballhive.h"
#include "SoundPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundPlayer::CSoundPlayer()
{

}

CSoundPlayer::~CSoundPlayer()
{
}


bool CSoundPlayer::Play(LPTSTR lpName, HINSTANCE hInst, bool bSync) 
{ 
	return PlaySound(lpName, NULL, SND_RESOURCE | (bSync ? SND_SYNC : SND_ASYNC)) ? true : false; 
}
