#include "includes.h"

int GetAngleDifference(Vec3& first, Vec3& second)
{
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

DWORD GetNearestPlayer()
{
	DWORD Target = NULL;
	DWORD LocalPlayer = *(DWORD*)(Game.GetClient() + offsets::dwLocalPlayer);
	DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);

	float OldDiff = FLT_MAX;
	float NewDiff = 0;

	for (int i = 1; i < 64; i++)
	{
		DWORD Entity = *(DWORD*)(Game.GetClient() + offsets::dwEntityList + i * constVars.PlayerStructSize);

		if (!Entity)
			continue;

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);
		int LocalPlayerTeam = *(int*)(LocalPlayer + offsets::m_iTeamNum);

		if (EntityTeam == LocalPlayerTeam)
			continue;

		int EntityHealth = *(int*)(Entity + offsets::m_iHealth);

		if (EntityHealth <= 0)
			continue;

		int CrosshairID = *(int*)(LocalPlayer + offsets::m_iCrosshairId);
		int SpottedByMask = *(int*)(Entity + offsets::m_bSpottedByMask);

		if (!(SpottedByMask & (1 << CrosshairID)))
			continue;

		Vec3 EntHeadPos = Game.GetPlayerBonePos(Entity, constVars.HeadBone);
		Vec3 LocalPos = *(Vec3*)(ClientState + offsets::dwClientState_ViewAngles);

		int Diff = GetAngleDifference(LocalPos, EntHeadPos);
		NewDiff = Diff;
		if ((Diff <= config::LegitAimBotDiff) && NewDiff < OldDiff)
		{
			OldDiff = NewDiff;
			Target = Entity;
		}
	}

	return Target;
}

void HACK::AimingAssistanceThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();
	DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);
	DWORD Entity = GetNearestPlayer();

	if (Entity != NULL)
	{
		Vec3 LocalPos = *(Vec3*)(LocalPlayer + offsets::m_vecOrigin);
		Vec3 EntPos = Game.GetPlayerBonePos(Entity, config::TargetBonePos);
		LocalPos.z += *(float*)(LocalPlayer + offsets::m_vecViewOffset + 0x8);

		Vec3 AngleTo = calcAngle(LocalPos, EntPos);

		if (config::SmoothAimBot)
			AngleTo = CalcSmoothAngle(LocalPos, EntPos);

		Vec3 ViewAngles = *(Vec3*)(ClientState + offsets::dwClientState_ViewAngles);

		Vec3 newAngles = normalizeAngles(AngleTo.x, AngleTo.y);

		*(Vec3*)(ClientState + offsets::dwClientState_ViewAngles) = newAngles;
	}
}