#include "includes.h"
#include "Vector.h"

DWORD GAME::GetClient()
{
	return (DWORD)GetModuleHandle("client.dll");
}

DWORD GAME::GetEngine()
{
	return (DWORD)GetModuleHandle("engine.dll");
}

DWORD GAME::GetLocalPlayer()
{
	return *(DWORD*)(GetClient() + offsets::dwLocalPlayer);
}

void GAME::PlayerShoot()
{
	DWORD client = GetClient();

	Sleep(CalcTriggerBotDelay(GetDistance(GetLocalPlayer())));
	*(int*)(client + offsets::dwForceAttack) = constVars.FlagsActive;
	Sleep(20);
	*(int*)(client + offsets::dwForceAttack) = constVars.FlagsOFF;
}

float GAME::CalcTriggerBotDelay(float Distance)
{
	float delay;

	switch (Game.GetCurrentWeapon())
	{
		case 262204:
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

float GAME::GetDistance(DWORD Entity)
{
	Vec3 myLocation = *(Vec3*)(Game.GetLocalPlayer() + offsets::m_vecOrigin);
	Vec3 enemyLocation = *(Vec3*)(Entity + offsets::m_vecOrigin);

	return sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
}

void GAME::PlayerJump()
{
	DWORD client = GetClient();

	*(int*)(client + offsets::dwForceJump) = constVars.FlagsActive;
	Sleep(config::BhopDelay);
	*(int*)(client + offsets::dwForceJump) = constVars.FlagsOFF;
}

Vec3 GAME::GetPlayerBonePos(DWORD Entity, int index)
{
	DWORD BoneMatrix = *(DWORD*)(Entity + offsets::m_dwBoneMatrix);

	static Vec3 Bone;

	Bone.x = *(float*)(BoneMatrix + 0x30 * index + 0xC);
	Bone.y = *(float*)(BoneMatrix + 0x30 * index + 0x1C);
	Bone.z = *(float*)(BoneMatrix + 0x30 * index + 0x2C);

	return Bone;
}

Vec3 GAME::GetCurrentWindowSize()
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

bool GAME::WorldToScreen(Vec3 pos, Vec3& out)
{
	Vec4 clipCoords;

	clipCoords.x = pos.x * ViewMatrix[0] + pos.y * ViewMatrix[1] + pos.z * ViewMatrix[2] + ViewMatrix[3];
	clipCoords.y = pos.x * ViewMatrix[4] + pos.y * ViewMatrix[5] + pos.z * ViewMatrix[6] + ViewMatrix[7];
	clipCoords.z = pos.x * ViewMatrix[8] + pos.y * ViewMatrix[9] + pos.z * ViewMatrix[10] + ViewMatrix[11];
	clipCoords.w = pos.x * ViewMatrix[12] + pos.y * ViewMatrix[13] + pos.z * ViewMatrix[14] + ViewMatrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	float WindowWidth = GetCurrentWindowSize().x;
	float WindowHeight = GetCurrentWindowSize().y;

	out.x = (WindowWidth / 2 * NDC.x) + (NDC.x + WindowWidth / 2);
	out.y = -(WindowHeight / 2 * NDC.y) + (NDC.y + WindowHeight / 2);

	return true;
}

short GAME::GetCurrentWeapon()
{
	DWORD LocalPlayer = GetLocalPlayer();

	int weapon = *(int*)(LocalPlayer + offsets::m_hActiveWeapon);
	int weaponEnt = *(int*)(GetClient() + offsets::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

	if (weaponEnt != NULL)
	{
		short weaponID = *(short*)(weaponEnt + offsets::m_iItemDefinitionIndex);

		return weaponID;
	}
		
	return -1;
}

short GAME::GetEntityWeapon(DWORD Entity)
{
	int weapon = *(int*)(Entity + offsets::m_hActiveWeapon);
	int weaponEnt = *(int*)(GetClient() + offsets::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

	if (weaponEnt != NULL)
	{
		short weaponID = *(short*)(weaponEnt + offsets::m_iItemDefinitionIndex);

		return weaponID;
	}

	return -1;
}

std::string GAME::GetWeaponName(int WeaponID)
{
	return WeaponNames[WeaponID];
}

void GAME::UpdateViewAngles()
{
	memcpy(&Game.ViewMatrix, (PBYTE*)(Game.GetClient() + offsets::dwViewMatrix), sizeof(Game.ViewMatrix));
}

bool GAME::CheckIfScoped()
{
	return *(bool*)(Game.GetLocalPlayer() + offsets::m_bIsScoped);
}

bool GAME::IsSniperWeapon(short CurrentWeapon)
{
	return (CurrentWeapon == WEAPON_AWP ||
			CurrentWeapon == WEAPON_SSG ||
			CurrentWeapon == WEAPON_SCAR20);
}