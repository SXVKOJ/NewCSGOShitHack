#include "includes.h"

void HACK::SetFov(int nFov)
{
	*(int*)(LOCALPLAYER + offsets::m_iDefaultFOV) = nFov;
}

void HACK::PlayerSetTPS(bool arg)
{
	*(bool*)(LOCALPLAYER + offsets::m_iObserverMode) = arg;
}

void HACK::SetCustomViewOffset(Vec3 nView)
{
	*(Vec3*)(LOCALPLAYER + offsets::m_vecViewOffset) = nView;
}