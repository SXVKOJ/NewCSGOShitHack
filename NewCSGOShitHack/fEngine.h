#pragma once
#include <Windows.h>
#include "Vector.h"

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

static struct myDevice
{
public:
	LPDIRECT3DDEVICE9 pDevice;

	VOID InitFonts();
	VOID InitLines();

	VOID DrawRect(int x, int y, int w, int h, D3DCOLOR color);
	VOID DrawBox(float x, float y, float w, float h, float px, D3DCOLOR color);
	VOID DrawLine(ID3DXLine* _Line, float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color);
	VOID DrawMessage(LPD3DXFONT& font, unsigned int x, unsigned int y, D3DCOLOR color, LPCSTR Message);

	HWND Window;
	HWND GetProcessWindow();
} mDevice;

static struct mEngine
{
public:
	int SkinChangerCFG[526];
	float ViewMatrix[16];

	Vec3 GetPlayerBonePos(uintptr_t &Entity, int index);
	Vec3 GetCurrentWindowSize();

	FLOAT CalcTriggerBotDelay(float Distance);
	FLOAT GetDistance(uintptr_t &Entity);
	
	VOID WorldToScreen(Vec3 pos, Vec3 &out);

	short GetEntityWeapon(uintptr_t &Entity);

	std::string GetWeaponName(short WeaponID);

	BOOL IsSniperWeapon(short CurrentWeapon);
} Engine;