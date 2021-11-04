#include "includes.h"

static Vec3 WindowSize = Engine.GetCurrentWindowSize();
static int ScreenMidX = WindowSize.x / 2;
static int ScreenMidY = WindowSize.y / 2;

int Hypotenuse(int FCathetus, int SCathetus)
{
	return sqrt(pow(FCathetus, 2) + pow(SCathetus, 2));
}

uintptr_t GetNearestPlayer()
{
	uintptr_t Target = NULL;

	float OldDiff = FLT_MAX;
	float NewDiff = 0;

	for (int i = 1; i < 64; i++)
	{
		uintptr_t Entity = *(uintptr_t*)(CLIENT + offsets::dwEntityList + i * cVars::PlayerStructSize);

		if (!Entity)
			continue;

		int EntityTeam = *(int*)(Entity + offsets::m_iTeamNum);

		if (EntityTeam == lPlayer.TeamNum())
			continue;

		int EntityHealth = *(int*)(Entity + offsets::m_iHealth);

		if (EntityHealth <= 0)
			continue;

		int CrosshairID = *(int*)(LOCALPLAYER + offsets::m_iCrosshairId);
		int SpottedByMask = *(int*)(Entity + offsets::m_bSpottedByMask);

		if (!(SpottedByMask & (1 << CrosshairID)))
			continue;

		Vec3 EntHeadPos = Engine.GetPlayerBonePos(Entity, cVars::HeadBone);
		Vec3 LocalPos = *(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);

		memcpy(&Engine.ViewMatrix, (PBYTE*)(CLIENT + offsets::dwViewMatrix), sizeof(Engine.ViewMatrix));

		Vec3 EntHeadW2S;
		Engine.WorldToScreen(EntHeadPos, EntHeadW2S);

		int DiffX = abs(ScreenMidX - EntHeadW2S.x);
		int DiffY = abs(ScreenMidY - EntHeadW2S.y);

		if (Hypotenuse(DiffX, DiffY) <= config::aimbot::LegitDiff)
		{
			Target = Entity;
			return Entity;
		}
	}

	return Target;
}

void HACK::AimingAssistanceThread()
{
	uintptr_t Entity = GetNearestPlayer();

	if (Entity != NULL)
	{
		Vec3 LocalPos = *(Vec3*)(LOCALPLAYER + offsets::m_vecOrigin);
		Vec3 EntityPos = Engine.GetPlayerBonePos(Entity, config::aimbot::TargetBonePos);
		LocalPos.z += *(float*)(LOCALPLAYER + offsets::m_vecViewOffset + 0x8);

		Vec3 AngleTo = calcAngle(LocalPos, EntityPos);

		Vec3 ViewAngles = *(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);

		Vec3 newAngles = normalizeAngles(AngleTo.x, AngleTo.y);

		*(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles) = GetSmoothAngle(ViewAngles, newAngles);
	}
}