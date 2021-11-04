#include "includes.h"

void HACK::NeonESPThread()
{
	for (int i = 1; i < 64; i++)
	{
		uintptr_t Entity = *(uintptr_t*)(CLIENT + offsets::dwEntityList + i * cVars::PlayerStructSize);
		uintptr_t GlowManager = *(uintptr_t*)(CLIENT + offsets::dwGlowObjectManager);

		if (!Entity)
			continue;

		int EntHealth = *(int*)(Entity + offsets::m_iHealth);
		int EntTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int GlowIndex = *(int*)(Entity + offsets::m_iGlowIndex);

		if (EntHealth <= 0)
			continue;

		if (EntTeam == lPlayer.TeamNum())
		{
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x8) = config::esp::colors::LT_GLOW[0];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0xC) = config::esp::colors::LT_GLOW[1];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x10) = config::esp::colors::LT_GLOW[2];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x14) = 1.7;
		}
		else
		{
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x8) = config::esp::colors::ET_GLOW[0];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0xC) = config::esp::colors::ET_GLOW[1];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x10) = config::esp::colors::ET_GLOW[2];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x14) = 1.7;
		}

		*(bool*)(GlowManager + (GlowIndex * 0x38) + 0x28) = TRUE;
		*(bool*)(GlowManager + (GlowIndex * 0x38) + 0x29) = FALSE;
	}
}