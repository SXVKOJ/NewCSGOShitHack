#pragma once
#include "Vector.h"

DWORD GetBestTarget();

Vec3 calcAngle(Vec3 lp, Vec3 ep);

Vec3 normalizeAngles(float x, float y);

int CalcHypotenuse(int f_cathetus, int s_cathetus);

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

	void SilentAimThread();

	void SpinBotThread(int speed);

	void SetCustomImGuiStyle();

	void SetFov(const int nFov);

	void MenuThread();

	void DXESPThread(LPDIRECT3DDEVICE9& pDevice);

	void DrawRect(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice);

	void DrawBox(float x, float y, float w, float h, float px, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice);

	void DrawLine(float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color, LPDIRECT3DDEVICE9& pDevice);
} Hack;