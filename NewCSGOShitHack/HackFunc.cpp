#include "includes.h"

void HACK::MainThread()
{
	if (GetAsyncKeyState(VK_SPACE) && config::hack::Bhop)
		Hack.BhopThread();

	if (config::hack::NeonWallHack)
		Hack.NeonESPThread();

	if (config::hack::TriggerBot && !config::hack::TriggerBotInAimBot)
		Hack.TriggerBotThread();

	if (config::hack::RecoilControlSystem)
		Hack.RecoilControlSystemThread();

	if (config::hack::SpinBot)
		Hack.SpinBotThread(config::aimbot::SpinBotSpeed);

	if (config::hack::RadarHack)
		Hack.RadarHackThread();

	if (config::hack::NoFlash)
		Hack.NoFlashThread();

	if (config::hack::AimingAssistance)
		Hack.AimingAssistanceThread();

	if (config::hack::ThirdPersonView && !config::hack::TPSActive)
	{
		Hack.PlayerSetTPS(TRUE);

		config::hack::TPSActive = TRUE;
	}

	if (!config::hack::ThirdPersonView && config::hack::TPSActive)
	{
		Hack.PlayerSetTPS(FALSE);

		config::hack::TPSActive = FALSE;
	}

	if (config::View::custom)
	{
		Hack.SetCustomViewOffset(Vec3{ config::View::offset_x, config::View::offset_y, config::View::offset_z });
	}

	if (config::hack::AimBot)
	{
		if (GetAsyncKeyState(config::HotKeys::AimBot))
		{
			Hack.AimBotThread();
		}
	}

	Hack.SetFov(config::hack::FOV);
}