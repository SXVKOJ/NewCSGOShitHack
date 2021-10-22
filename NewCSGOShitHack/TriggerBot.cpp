#include "includes.h"

void HACK::TriggerBotThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();
	DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);

	int CrosshairID = *(int*)(LocalPlayer + offsets::m_iCrosshairId);

	if (CrosshairID != 0 && CrosshairID < 64)
	{ 
		DWORD Entity = *(DWORD*)(Game.GetClient() + offsets::dwEntityList + (CrosshairID - 1) * constVars.PlayerStructSize);

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int LocalPlayerTeam = *(int*)(LocalPlayer + offsets::m_iTeamNum);
		short CurrentWeapon = Game.GetCurrentWeapon();

		if (LocalPlayerTeam != EntityTeam)
		{
			if (config::Aim::Compensation)
			{
				Vec3 ViewAngles = *(Vec3*)(ClientState + offsets::dwClientState_ViewAngles);
				*(float*)(ClientState + offsets::dwClientState_ViewAngles) = ViewAngles.x + USER_COMP_CFG[Game.GetCurrentWeapon()];
			}

			if (Game.IsSniperWeapon(CurrentWeapon))
			{
				if (Game.CheckIfScoped())
				{
					Game.PlayerShoot();
				}
			}
			else 
				Game.PlayerShoot();
		}
	}
}