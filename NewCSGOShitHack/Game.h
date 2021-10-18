#pragma once
#include "Vector.h"

static struct GAME
{
	std::string GetWeaponName(int Weapon);

	float ViewMatrix[16];

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