#include "includes.h"

IDirect3DTexture9* tImage = nullptr;

void HACK::LoadImageToDll(BYTE* Image, LPDIRECT3DDEVICE9& pDevice)
{
	if (tImage == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(pDevice, &NameArry, sizeof(NameArry), 495, 659, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tImage);
}

void HACK::MainThread()
{
	if (Bhop && GetAsyncKeyState(VK_SPACE))
		Hack.BhopThread();

	if (NeonWallHack)
		Hack.NeonESPThread();

	if (TriggerBot && !TriggerBotInAimBot)
		Hack.TriggerBotThread();

	if (RecoilControlSystem)
		Hack.RecoilControlSystemThread();

	if (SpinBot)
		Hack.SpinBotThread(SpinBotSpeed);

	if (RadarHack)
		Hack.RadarHackThread();

	if (NoFlash)
		Hack.NoFlashThread();

	if (AimingAssistance)
		Hack.AimingAssistanceThread();

	if (ThirdPersonView && !TPSActive)
	{
		Hack.PlayerSetTPS(true);

		TPSActive = true;
	}

	if (!ThirdPersonView && TPSActive)
	{
		Hack.PlayerSetTPS(false);

		TPSActive = false;
	}
	
	if (AimBot)
	{
		if (GetAsyncKeyState(AimBotHotKey))
		{
			Hack.AimBotThread();
		}
	}

	Hack.SetFov(FOV);

	if (AimBot && AimingAssistance)
		AimBot = !AimBot;
}