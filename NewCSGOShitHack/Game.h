#pragma once

static struct GAME
{
	DWORD GetClient();

	DWORD GetEngine();

	DWORD GetLocalPlayer();

	void PlayerJump();

	Vec3 GetPlayerBonePos(DWORD Entity, int index);

	void PlayerShoot();
} Game;

static struct CONSOLE
{
	FILE* Init();

	void Release(FILE * filePtr);
} Console;