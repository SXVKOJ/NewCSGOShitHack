#include "includes.h"

void HACK::NoFlashThread()
{
	DWORD LocalPlayer = *(DWORD*)(Game.GetClient() + offsets::dwLocalPlayer);

	if (LocalPlayer + offsets::m_flFlashDuration > 0)
	{
		*(int*)(LocalPlayer + offsets::m_flFlashDuration) = constVars.InActive;
	}
}