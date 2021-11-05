#pragma once
#include "Vector.h"
#include <Windows.h>

static class HACK
{
public:
	VOID MainThread();

	VOID BhopThread();

	VOID NeonESPThread();

	VOID TriggerBotThread();

	VOID AimBotThread();

	VOID RecoilControlSystemThread();

	VOID RadarHackThread();

	VOID NoFlashThread();

	VOID FullForceUpdate();

	VOID AimingAssistanceThread();

	VOID SkinChangerThread();

	VOID SpinBotThread(int speed);

	VOID ESPDrawBonesThread();

	VOID SetFov(const int nFov);

	VOID SetCustomViewOffset(Vec3 nView);

	VOID PlayerSetTPS(bool arg);

	VOID DXESPThread();
} Hack;

uintptr_t GetBestTarget();

Vec3 calcAngle(Vec3 lp, Vec3 ep);

Vec3 normalizeAngles(float x, float y);

Vec3 CalcSmoothAngle(Vec3 src, Vec3 dst);

Vec3 GetSmoothAngle(Vec3 dest, Vec3 orig);
