#include "includes.h"

void HACK::NoFlashThread()
{
	if (*(int*)(LOCALPLAYER + offsets::m_flFlashDuration) > 0)
	{
		*(int*)(LOCALPLAYER + offsets::m_flFlashDuration) = cVars::Flags::OFF;
	}
}