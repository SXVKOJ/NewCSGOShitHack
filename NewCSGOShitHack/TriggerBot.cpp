#include "includes.h"

void HACK::TriggerBotThread()
{
	int CrosshairID = *(int*)(LOCALPLAYER + offsets::m_iCrosshairId);

	if (CrosshairID != 0 && CrosshairID < 64)
	{ 
		uintptr_t Entity = *(uintptr_t*)(CLIENT + offsets::dwEntityList + (CrosshairID - 1) * cVars::PlayerStructSize);

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);
		short CurrentWeapon = lPlayer.GetCurrentWeapon();

		if (lPlayer.TeamNum() != EntityTeam)
		{
			if (Engine.IsSniperWeapon(CurrentWeapon))
			{
				if (lPlayer.CheckIfScoped())
				{
					lPlayer.Shoot();
					Sleep(config::aimbot::SniperWeaponTriggerBotCooldown);
				}
			}
			else
				lPlayer.Shoot();
		}
	}
}