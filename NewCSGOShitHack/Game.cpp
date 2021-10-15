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

	*(int*)(client + offsets::dwForceAttack) = constVars.FlagsActive;
	if (config::TriggerBotCooldown > 20)
		Sleep(config::TriggerBotCooldown);
	*(int*)(client + offsets::dwForceAttack) = constVars.FlagsOFF;
}

void GAME::PlayerJump()
{
	DWORD client = GetClient();

	*(int*)(client + offsets::dwForceJump) = constVars.FlagsActive;
	if (config::BhopDelay >= 15)
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

int GAME::GetCurrentWeapon()
{
	DWORD LocalPlayer = GetLocalPlayer();

	int weapon = *(int*)(LocalPlayer + offsets::m_hActiveWeapon);
	int weaponEnt = *(int*)(GetClient() + offsets::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);
	int weaponID = *(int*)(weaponEnt + offsets::m_iItemDefinitionIndex);

	return weaponID;
}