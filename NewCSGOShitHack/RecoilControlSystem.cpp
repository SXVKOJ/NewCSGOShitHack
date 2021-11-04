#include "includes.h"

float oPunchX = 0;
float oPunchY = 0;

void HACK::RecoilControlSystemThread()
{
	int ShotsFired = *(int*)(LOCALPLAYER + offsets::m_iShotsFired);

	if (ShotsFired >= 1 && GetAsyncKeyState(VK_LBUTTON))
	{
		Vec3 ViewAngles = *(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);

		float PunchX = *(float*)(LOCALPLAYER + offsets::m_aimPunchAngle) * 2;
		float PunchY = *(float*)(LOCALPLAYER + offsets::m_aimPunchAngle + 0x4) * 2;

		float n_x = (ViewAngles.x + oPunchX) - PunchX;
		float n_y = (ViewAngles.y + oPunchY) - PunchY;

		*(float*)(CLIENTSTATE + offsets::dwClientState_ViewAngles)       = n_x;
		*(float*)(CLIENTSTATE + offsets::dwClientState_ViewAngles + 0x4) = n_y;

		oPunchX = PunchX;
		oPunchY = PunchY;
	}
	else
	{
		oPunchX = 0;
		oPunchY = 0;
	}
}