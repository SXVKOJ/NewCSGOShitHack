#include "includes.h"

float CalcHypotenuse(float f_cathetus, float s_cathetus)
{
	return sqrtf((f_cathetus * f_cathetus) + (s_cathetus * s_cathetus));
}

DWORD GetBestTarget()
{
	DWORD Target = NULL;

	float OldDistance = FLT_MAX;
	float NewDistance = 0;

	DWORD LocalPlayer = *(DWORD*)(Game.GetClient() + offsets::dwLocalPlayer);

	for (int i = 1; i < 64; i++)
	{
		DWORD Entity = *(DWORD*)(Game.GetClient() + offsets::dwEntityList + i * constVars.PlayerStructSize);

		if (!Entity)
			continue;

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int LocalPlayerTeam = *(int*)(LocalPlayer + offsets::m_iTeamNum);

		int EntityHealth = *(int*)(Entity + offsets::m_iHealth);

		// if health is less than a certain threshold, then the aimbot will automatically select this player
		if (Config.HealthTreshold && EntityHealth <= Config.HealthTresholdVal)	
			return Entity;

		Vec3 EntHeadPos = 
	}
}

void HACK::AimBotThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();
}