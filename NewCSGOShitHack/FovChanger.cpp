#include "includes.h"

void HACK::SetFov(int nFov)
{
	DWORD LocalPlayer = Game.GetLocalPlayer();

	*(int*)(LocalPlayer + offsets::m_iDefaultFOV) = nFov;
}