#include "includes.h"

void HACK::MainThread()
{
	if (config::Bhop && GetAsyncKeyState(VK_SPACE))
		Hack.BhopThread();

	if (config::NeonWallHack)
		Hack.NeonESPThread();

	if (config::TriggerBot && !config::TriggerBotInAimBot)
		Hack.TriggerBotThread();

	if (config::RecoilControlSystem)
		Hack.RecoilControlSystemThread();

	if (config::SpinBot)
		Hack.SpinBotThread(config::SpinBotSpeed);

	if (config::RadarHack)
		Hack.RadarHackThread();

	if (config::NoFlash)
		Hack.NoFlashThread();

	if (config::AimingAssistance)
		Hack.AimingAssistanceThread();

	if (config::ThirdPersonView && !config::TPSActive)
	{
		Hack.PlayerSetTPS(true);

		config::TPSActive = true;
	}

	if (!config::ThirdPersonView && config::TPSActive)
	{
		Hack.PlayerSetTPS(false);

		config::TPSActive = false;
	}
	
	if (config::AimBot)
	{
		if (GetAsyncKeyState(config::AimBotHotKey))
		{
			Hack.AimBotThread();
		}
	}

	Hack.SetFov(config::FOV);

	if (config::AimBot && config::AimingAssistance)
		config::AimBot = !config::AimBot;
}