#include "includes.h"

float oPunchX = 0;
float oPunchY = 0;

void HACK::RecoilControlSystemThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();
	DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);

	int ShotsFired = *(int*)(LocalPlayer + offsets::m_iShotsFired);

	if (ShotsFired >= 3)
	{
		Vec3 ViewAngles = *(Vec3*)(ClientState + offsets::dwClientState_ViewAngles);

		float PunchX = *(float*)(LocalPlayer + offsets::m_aimPunchAngle) * 2;
		float PunchY = *(float*)(LocalPlayer + offsets::m_aimPunchAngle + 0x4) * 2;

		float n_x = (ViewAngles.x + oPunchX) - PunchX;
		float n_y = (ViewAngles.y + oPunchY) - PunchY;

		*(float*)(ClientState + offsets::dwClientState_ViewAngles) = n_x;
		*(float*)(ClientState + offsets::dwClientState_ViewAngles + 0x4) = n_y;

		oPunchX = PunchX;
		oPunchY = PunchY;
	}
	else
	{
		oPunchX = 0;
		oPunchY = 0;
	}
}