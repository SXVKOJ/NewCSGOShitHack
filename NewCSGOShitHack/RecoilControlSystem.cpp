#include "includes.h"

float oPunchX = 0;
float oPunchY = 0;

void HACK::RecoilControlSystemThread()
{
	int ShotsFired = *(int*)(LOCALPLAYER + offsets::m_iShotsFired);

	if (ShotsFired >= 1)
	{
		Vec3 ViewAngles = lPlayer.ViewAngles();

		float PunchX = *(float*)(LOCALPLAYER + offsets::m_aimPunchAngle) * 2;
		float PunchY = *(float*)(LOCALPLAYER + offsets::m_aimPunchAngle + 0x4) * 2;

		float n_x = (ViewAngles.x + oPunchX) - PunchX;
		float n_y = (ViewAngles.y + oPunchY) - PunchY;

		lPlayer.SetViewAngles(Vec3{ n_x, n_y,0 });

		oPunchX = PunchX;
		oPunchY = PunchY;
	}
	else
	{
		oPunchX = 0;
		oPunchY = 0;
	}
}