#include "includes.h"
# define M_PI           3.14159265358979323846

int CalcHypotenuse(int f_cathetus, int s_cathetus)
{
	return sqrt((f_cathetus * f_cathetus) + (s_cathetus * s_cathetus));
}

Vec3 calcAngle(Vec3 lp, Vec3 ep)
{
	float d_x = lp.x - ep.x;
	float d_y = lp.y - ep.y;
	float d_z = lp.z - ep.z;

	float hyp = sqrt(d_x * d_x + d_y * d_y + d_z * d_z);

	float x = atan(d_z / hyp) * 180 / M_PI;
	float y = atan(d_y / d_x) * 180 / M_PI;

	if (d_x > 0.0)
	{
		y += 180;
	}

	return Vec3{ x, y, 0 };
}

Vec3 normalizeAngles(float x, float y)
{
	if (x > 89)
	{
		x -= 360;
	}
	else if (x < -89)
	{
		x += 360;
	}
	else if (y > 180)
	{
		y -= 360;
	}
	else if (y < -180)
	{
		y += 360;
	}

	return Vec3{ x, y, 0 };
}

DWORD GetBestTarget()
{
	DWORD Target = NULL;

	float OldDiff = FLT_MAX;
	float NewDiff = 0;

	DWORD LocalPlayer = *(DWORD*)(Game.GetClient() + offsets::dwLocalPlayer);

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

		// if health is less than a certain threshold, then the aimbot will automatically select this player
		if (Config.HealthTreshold && EntityHealth <= Config.HealthTresholdVal)	
			return Entity;

		Vec3 EntHeadPos = Game.GetPlayerBonePos(Entity, constVars.HeadBone);
		Vec3 WorldEntHeadPos;	Game.WorldToScreen(EntHeadPos, WorldEntHeadPos);

		float ScreenMiddleX = Game.GetCurrentWindowSize().x;
		float ScreenMiddleY = Game.GetCurrentWindowSize().y;

		float DiffX = abs(ScreenMiddleX - WorldEntHeadPos.x);
		float DiffY = abs(ScreenMiddleY - WorldEntHeadPos.y);

		float ResultDiff = CalcHypotenuse(DiffX, DiffY);

		NewDiff = ResultDiff;

		if (NewDiff <= OldDiff)
		{
			OldDiff = NewDiff;
			Target = Entity;
		}
	}

	return Target;
}

void HACK::AimBotThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();
	DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);

	if (GetBestTarget() != NULL)
	{	
		DWORD Entity = GetBestTarget();

		if (GetAsyncKeyState(Config.AimBotHotKey) == 0)
		{
			return;
		}

		Vec3 LocalPos = *(Vec3*)(LocalPlayer + offsets::m_vecOrigin);
		Vec3 EntPos = Game.GetPlayerBonePos(Entity, constVars.HeadBone);
		LocalPos.z += *(float*)(LocalPlayer + offsets::m_vecViewOffset + 0x8);

		Vec3 AngleTo = calcAngle(LocalPos, EntPos);
		Vec3 ViewAngles = *(Vec3*)(ClientState + offsets::dwClientState_ViewAngles);

		Vec3 newAngles = normalizeAngles(AngleTo.x - ViewAngles.x, AngleTo.y - ViewAngles.y);

		*(Vec3*)(ClientState + offsets::dwClientState_ViewAngles) = ViewAngles + newAngles;

		int EntityHealth = *(int*)(Entity + offsets::m_iHealth);

		if (EntityHealth <= 0)
		{
			return;
		}
	}
}