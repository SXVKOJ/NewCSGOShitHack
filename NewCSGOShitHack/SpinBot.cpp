#include "includes.h"

static bool SpinInit = false;

void HACK::SpinBotThread(int speed)
{
	DWORD LocalPlayer = Game.GetLocalPlayer();
	DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);

	if (!SpinInit)
	{
		// Set ViewAngle to 0
		*(float*)(ClientState + offsets::dwClientState_ViewAngles + 0x4) = 0;
		SpinInit = true;
	}

	float x = *(float*)(ClientState + offsets::dwClientState_ViewAngles);
	float y = *(float*)(ClientState + offsets::dwClientState_ViewAngles + 0x4);

	*(float*)(ClientState + offsets::dwClientState_ViewAngles) = 89;
	*(float*)(ClientState + offsets::dwClientState_ViewAngles + 0x4) = y - speed;

	if (y == -179.f)
		*(float*)(ClientState + offsets::dwClientState_ViewAngles + 0x4) = 180;
}