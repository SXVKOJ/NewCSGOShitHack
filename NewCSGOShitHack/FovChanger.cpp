#include "includes.h"

void HACK::SetFov(int nFov)
{
	DWORD LocalPlayer = Game.GetLocalPlayer();

	*(int*)(LocalPlayer + offsets::m_iDefaultFOV) = nFov;
}

void HACK::PlayerSetTPS(bool arg)
{
	DWORD LocalPlayer = Game.GetLocalPlayer();

	*(bool*)(LocalPlayer + offsets::m_iObserverMode) = arg;
}