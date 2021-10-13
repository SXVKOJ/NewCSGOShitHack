#include "includes.h"

void HACK::TriggerBotThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();

	int CrosshairID = *(int*)(LocalPlayer + offsets::m_iCrosshairId);

	if (CrosshairID != 0 && CrosshairID < 64)
	{ 
		DWORD Entity = *(DWORD*)(Game.GetClient() + offsets::dwEntityList + (CrosshairID - 1) * constVars.PlayerStructSize);

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int LocalPlayerTeam = *(int*)(LocalPlayer + offsets::m_iTeamNum);

		if (LocalPlayerTeam != EntityTeam)
		{
			Game.PlayerShoot();

			Sleep(TriggerBotDelay);
		}
	}
}