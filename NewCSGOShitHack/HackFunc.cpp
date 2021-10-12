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
		Hack.SpinBotThread(Config.SpinBotSpeed);

	if (RadarHack)
		Hack.RadarHackThread();

	if (NoFlash)
		Hack.NoFlashThread();

	if (AimBot)
	{
		if (GetAsyncKeyState(AimBotHotKey))
		{
			Hack.AimBotThread();
		}
	}

	Hack.SetFov(FOV);
}