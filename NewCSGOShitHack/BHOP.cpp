#include "includes.h"

void HACK::BhopThread()
{
	DWORD LocalPlayer = Game.GetLocalPlayer();

	int PlayerFlags = *(int*)(LocalPlayer + offsets::m_fFlags);
	
	Vec3 PlayerVel = *(Vec3*)(Game.GetLocalPlayer() + offsets::m_vecVelocity);

	if (PlayerFlags == constVars.FlagsOnGround)
	{
		if (PlayerVel.x - 1e-6 != 0 && PlayerVel.y - 1e-6 != 0)
		{
			Game.PlayerJump();
		}
	}
}	