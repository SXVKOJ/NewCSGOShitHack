#include "includes.h"

void HACK::RadarHackThread()
{
	for (int i = 1; i < 64; i++)
	{
		uintptr_t Entity = *(uintptr_t*)(CLIENT + offsets::dwEntityList + i * cVars::PlayerStructSize);

		if (!Entity)
			continue;

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int LocalPlayerTeam = *(int*)(LOCALPLAYER + offsets::m_iTeamNum);

		if (EntityTeam == LocalPlayerTeam)
			continue;

		int EntityHealth = *(int*)(Entity + offsets::m_iHealth);

		if (EntityHealth <= 0)
			continue;

		*(bool*)(Entity + offsets::m_bSpotted) = TRUE;
	}
}