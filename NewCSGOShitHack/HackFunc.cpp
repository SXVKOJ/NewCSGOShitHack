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
		Hack.RecoilControlSystem();
	}

	if (Config.RadarHack)
	{
		Hack.RadarHack();
	}

	if (Config.AimBot && GetAsyncKeyState(Config.AimBotHotKey))
	{
		Hack.AimBotThread();
	}
}