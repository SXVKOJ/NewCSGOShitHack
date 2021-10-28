#pragma once
#include "Vector.h"

static struct GAME
{
	float ViewMatrix[16];

	bool CheckIfScoped();

	float GetDistance(DWORD Entity);

	float CalcTriggerBotDelay(float Distance);

	bool IsSniperWeapon(short CurrentWeapon);

	void UpdateViewAngles();

	std::string GetWeaponName(int Weapon);

	DWORD GetClient();

	DWORD GetEngine();

	DWORD GetLocalPlayer();

	short GetEntityWeapon(DWORD Entity);

	void PlayerJump();

	Vec3 GetPlayerBonePos(DWORD Entity, int index);

	Vec3 GetCurrentWindowSize();

	bool WorldToScreen(Vec3 pos, Vec3& out);

	void PlayerShoot();

	short GetCurrentWeapon();
} Game;

static struct CONSOLE
{
	FILE* Init();

	void Release(FILE * filePtr);
} Console;