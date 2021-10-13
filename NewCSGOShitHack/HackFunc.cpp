#include "includes.h"

void HACK::MainThread()
{
	if (Bhop && GetAsyncKeyState(VK_SPACE))
		Hack.BhopThread();

	if (NeonWallHack)
		Hack.NeonESPThread();

	if (TriggerBot)
		Hack.TriggerBotThread();

	if (RecoilControlSystem)
		Hack.RecoilControlSystemThread();

	if (SpinBot)
		Hack.SpinBotThread(SpinBotSpeed);

	if (RadarHack)
		Hack.RadarHackThread();

	if (NoFlash)
		Hack.NoFlashThread();

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
}