#include "includes.h"

void HACK::BhopThread()
{
	if (lPlayer.Flags() == cVars::Flags::OnGround)
	{
		if (lPlayer.Velocity().x != 0 &&
			lPlayer.Velocity().y != 0)
		{
			lPlayer.Jump();
		}
	}
}	