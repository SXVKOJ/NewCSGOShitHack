#include "includes.h"

static bool SpinInit = false;

void HACK::SpinBotThread(int speed)
{
	if (!SpinInit)
	{
		// Set ViewAngle to 0
		*(float*)(CLIENTSTATE + offsets::dwClientState_ViewAngles + 0x4) = 0;
		SpinInit = true;
	}

	float x = *(float*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);
	float y = *(float*)(CLIENTSTATE + offsets::dwClientState_ViewAngles + 0x4);

	lPlayer.SetViewAngles(Vec3{ 89, (y - speed), 0 });

	if (y == -179.f)
		*(float*)(CLIENTSTATE + offsets::dwClientState_ViewAngles + 0x4) = 180;
}