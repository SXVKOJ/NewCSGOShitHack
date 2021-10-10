#include "includes.h"

void HACK::MainThread()
{
	if (Config.Bhop && GetAsyncKeyState(VK_SPACE))
	{
		Hack.BhopThread();
	}

	if (Config.NeonWallHack)
	{
		Hack.NeonESPThread();
	}

	if (Config.TriggerBot)
	{
		Hack.TriggerBotThread();
	}

	if (Config.RecoilControlSystem)
	{
		Hack.RecoilControlSystemThread();
	}

	if (Config.RadarHack)
	{
		Hack.RadarHackThread();
	}

	if (Config.NoFlash)
	{
		Hack.NoFlashThread();
	}

	if (Config.AimBot)
	{
		if (GetAsyncKeyState(Config.AimBotHotKey))
		{
			Hack.AimBotThread();
		}	
	}
}