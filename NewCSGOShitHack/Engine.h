#pragma once
#include <Windows.h>

static class mEngine
{
public:
	int SkinChangerCFG[70];
	float ViewMatrix[16];

	Vec3 GetPlayerBonePos(uintptr_t& Entity, int index);
	Vec3 GetCurrentWindowSize();

	VOID WorldToScreen(Vec3 pos, Vec3& out);

	short GetEntityWeapon(uintptr_t& Entity);

	std::string GetWeaponName(short WeaponID);

	BOOL IsSniperWeapon(short CurrentWeapon);
} Engine;

namespace dx
{
	namespace fonts
	{
		extern LPD3DXFONT health_font;
		extern LPD3DXFONT weapon_font;

	}
	namespace lines
	{
		extern ID3DXLine* espLine;
		extern ID3DXLine* espBoxLine;
		extern ID3DXLine* HealthBarLine;
		extern ID3DXLine* ArmorBarLine;
	}
}

namespace TriggerBot
{
	FLOAT CalcTriggerBotDelay(float Distance);
	FLOAT GetDistanceToEntity(uintptr_t& Entity);
}