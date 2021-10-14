#include "includes.h"

void HACK::NeonESPThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();

	int LocalPlayerTeam = *(int*)(LocalPlayer + offsets::m_iTeamNum);

	for (int i = 1; i < 64; i++)
	{
		DWORD Entity = *(DWORD*)(Game.GetClient() + offsets::dwEntityList + i * constVars.PlayerStructSize);
		DWORD GlowManager = *(DWORD*)(Game.GetClient() + offsets::dwGlowObjectManager);

		if (!Entity)
			continue;

		int EntHealth = *(int*)(Entity + offsets::m_iHealth);
		int EntTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int GlowIndex = *(int*)(Entity + offsets::m_iGlowIndex);

		if (EntHealth <= 0)
			continue;

		if (EntTeam == LocalPlayerTeam)
		{
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x8) = config::LT_NEONESP[0];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0xC) = config::LT_NEONESP[1];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x10) = config::LT_NEONESP[2];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x14) = 1.7;
		}
		else
		{
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x8) = config::ET_NEONESP[0];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0xC) = config::ET_NEONESP[1];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x10) = config::ET_NEONESP[2];
			*(float*)(GlowManager + (GlowIndex * 0x38) + 0x14) = 1.7;
		}

		*(bool*)(GlowManager + (GlowIndex * 0x38) + 0x28) = true;
		*(bool*)(GlowManager + (GlowIndex * 0x38) + 0x29) = false;
	}
}