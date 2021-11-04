#pragma once
#include "Vector.h"
#include <Windows.h>

uintptr_t GetBestTarget();

Vec3 calcAngle(Vec3 lp, Vec3 ep);

Vec3 normalizeAngles(float x, float y);

Vec3 CalcSmoothAngle(Vec3 src, Vec3 dst);

Vec3 GetSmoothAngle(Vec3 dest, Vec3 orig);

static struct HACK
{
	void MainThread();

	void BhopThread();

	void NeonESPThread();

	void TriggerBotThread();

	void AimBotThread();

	void RecoilControlSystemThread();

	void RadarHackThread();

	void NoFlashThread();

	void FullForceUpdate();

	void AimingAssistanceThread();

	void SkinChangerThread();

	void SpinBotThread(int speed);

	void ESPDrawBonesThread();

	void SetFov(const int nFov);

	void SetCustomViewOffset(Vec3 nView);

	void PlayerSetTPS(bool arg);

	void DXESPThread();
} Hack;
