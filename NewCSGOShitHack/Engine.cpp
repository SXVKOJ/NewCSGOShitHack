#include "includes.h"
#include "Vector.h"

FLOAT TriggerBot::CalcTriggerBotDelay(float Distance)
{
	float delay;

	switch (lPlayer.GetCurrentWeapon())
	{
	case 26:
		delay = 3;
	case 7:
		delay = 3.3;
	case 40:
		delay = 0.15;
	case 9:
		delay = 0.15;
	default:
		delay = 0;
	}

	return delay * Distance;
}

FLOAT TriggerBot::GetDistanceToEntity(uintptr_t& Entity)
{
	Vec3 myLocation = *(Vec3*)(LOCALPLAYER + offsets::m_vecOrigin);
	Vec3 enemyLocation = *(Vec3*)(Entity + offsets::m_vecOrigin);

	return sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
}

Vec3 mEngine::GetPlayerBonePos(uintptr_t& Entity, int index)
{
	uintptr_t BoneMatrix = *(uintptr_t*)(Entity + offsets::m_dwBoneMatrix);

	static Vec3 Bone;

	Bone.x = *(float*)(BoneMatrix + 0x30 * index + 0xC);
	Bone.y = *(float*)(BoneMatrix + 0x30 * index + 0x1C);
	Bone.z = *(float*)(BoneMatrix + 0x30 * index + 0x2C);

	return Bone;
}

Vec3 mEngine::GetCurrentWindowSize()
{
	HWND CsgoHandle = FindWindowA(NULL, "Counter-Strike: Global Offensive");

	RECT rect;

	float width = 0;
	float height = 0;

	if (GetWindowRect(CsgoHandle, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	return Vec3{ width, height, 0 };
}

VOID mEngine::WorldToScreen(Vec3 pos, Vec3& out)
{
	Vec4 clipCoords;

	clipCoords.x = pos.x * ViewMatrix[0] + pos.y * ViewMatrix[1] + pos.z * ViewMatrix[2] + ViewMatrix[3];
	clipCoords.y = pos.x * ViewMatrix[4] + pos.y * ViewMatrix[5] + pos.z * ViewMatrix[6] + ViewMatrix[7];
	clipCoords.z = pos.x * ViewMatrix[8] + pos.y * ViewMatrix[9] + pos.z * ViewMatrix[10] + ViewMatrix[11];
	clipCoords.w = pos.x * ViewMatrix[12] + pos.y * ViewMatrix[13] + pos.z * ViewMatrix[14] + ViewMatrix[15];

	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	float WindowWidth = GetCurrentWindowSize().x;
	float WindowHeight = GetCurrentWindowSize().y;

	out.x = (WindowWidth / 2 * NDC.x) + (NDC.x + WindowWidth / 2);
	out.y = -(WindowHeight / 2 * NDC.y) + (NDC.y + WindowHeight / 2);
}

short mEngine::GetEntityWeapon(uintptr_t &Entity)
{
	int weapon = *(int*)(Entity + offsets::m_hActiveWeapon);
	int weaponEnt = *(int*)(CLIENT + offsets::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

	if (weaponEnt)
	{
		short weaponID = *(short*)(weaponEnt + offsets::m_iItemDefinitionIndex);

		return weaponID;
	}
	return NULL;
}

std::string mEngine::GetWeaponName(short WeaponID)
{
	return WeaponNames[WeaponID];
}

BOOL mEngine::IsSniperWeapon(short CurrentWeapon)
{
	return (CurrentWeapon == WEAPON_AWP ||
			CurrentWeapon == WEAPON_SSG ||
			CurrentWeapon == WEAPON_SCAR20);
}