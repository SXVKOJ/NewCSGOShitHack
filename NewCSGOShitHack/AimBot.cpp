#include "includes.h"
# define M_PI           3.14159265358979323846

Vec3 Subtract(Vec3 src, Vec3 dst)
{
	Vec3 diff;
	diff.x = src.x - dst.x;
	diff.y = src.y - dst.y;
	diff.z = src.z - dst.z;
	return diff;
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
		y += 180;

	return Vec3{ (float)x,(float)y, 0 };
}

Vec3 CalcSmoothAngle(Vec3 src, Vec3 dst)
{
	float delta[3] = { (src.x - dst.x), (src.y - dst.y), (src.z - dst.z) };
	float hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

	Vec3 aimBotAngle;
	aimBotAngle.x = (float)(atanf(delta[2] / hyp) * 57.295779513082f);
	aimBotAngle.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
	aimBotAngle.z = 0.0f;

	if (delta[0] >= 0.0)
		aimBotAngle.y += 180.0f;

	return aimBotAngle;
}

Vec3 GetSmoothAngle(Vec3 dest, Vec3 orig)
{
	Vec3 delta;
	delta.x = orig.x - dest.x;
	delta.y = orig.y - dest.y;

	dest.x = orig.x - delta.x / (5.f * config::aimbot::SmoothVal);
	dest.y = orig.y - delta.y / (5.f * config::aimbot::SmoothVal);

	return dest;
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

float Magnitude(Vec3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float Distance(Vec3 src, Vec3 dst)
{
	Vec3 diff = Subtract(src, dst);
	return Magnitude(diff);
}

uintptr_t GetBestTarget()
{
	uintptr_t Target = NULL;

	float OldDiff = FLT_MAX;
	float NewDiff = 0;

	uintptr_t LocalPlayer = *(uintptr_t*)(CLIENT + offsets::dwLocalPlayer);

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

		int CrosshairID = *(int*)(LocalPlayer + offsets::m_iCrosshairId);
		int SpottedByMask = *(int*)(Entity + offsets::m_bSpottedByMask);

		if (!(SpottedByMask & (1 << CrosshairID)) && config::aimbot::LegitMode)
			continue;

		Vec3 EntHeadPos = Engine.GetPlayerBonePos(Entity, cVars::HeadBone);
		Vec3 LocalPos = *(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);

		Vec3 AngleTo = calcAngle(LocalPos, EntHeadPos);

		NewDiff = AngleTo.x;
		if (NewDiff < OldDiff)
		{
			OldDiff = NewDiff;
			Target = Entity;
		}
	}

	return Target;
}

void HACK::AimBotThread()
{
	uintptr_t Entity = GetBestTarget();

	if (Entity != NULL)
	{	
		Vec3 LocalPos = *(Vec3*)(LOCALPLAYER + offsets::m_vecOrigin);
		Vec3 EntPos = Engine.GetPlayerBonePos(Entity, config::aimbot::TargetBonePos);
		LocalPos.z += *(float*)(LOCALPLAYER + offsets::m_vecViewOffset + 0x8);

		Vec3 AngleTo = calcAngle(LocalPos, EntPos);
		
		Vec3 ViewAngles = *(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);

		Vec3 newAngles = normalizeAngles(AngleTo.x, AngleTo.y);

		*(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles) = GetSmoothAngle(ViewAngles, newAngles);
	}
}