#include "includes.h"

VOID LocalPlayer::Shoot(uintptr_t& Entity)
{
	uintptr_t client = CLIENT;

	*(int*)(client + offsets::dwForceAttack) = cVars::Flags::Active;
	Sleep(20);
	*(int*)(client + offsets::dwForceAttack) = cVars::Flags::InActive;
}

VOID LocalPlayer::Jump()
{
	uintptr_t client = CLIENT;

	*(int*)(client + offsets::dwForceJump) = cVars::Flags::Active;
	Sleep(17);
	*(int*)(client + offsets::dwForceJump) = cVars::Flags::InActive;
}

VOID LocalPlayer::SetViewAngles(Vec3 dest)
{
	uintptr_t ClientState = CLIENTSTATE;

	*(Vec3*)(ClientState + offsets::dwClientState_ViewAngles) = dest;
}

short LocalPlayer::GetCurrentWeapon()
{
	int weapon = *(int*)(LOCALPLAYER + offsets::m_hActiveWeapon);
	int weaponEnt = *(int*)(CLIENT + offsets::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

	if (weaponEnt)
	{
		short weaponID = *(short*)(weaponEnt + offsets::m_iItemDefinitionIndex);

		return weaponID;
	}
	return NULL;
}

Vec3 LocalPlayer::Velocity()
{
	return *(Vec3*)(LOCALPLAYER + offsets::m_vecVelocity);
}

Vec3 LocalPlayer::Position()
{
	return *(Vec3*)(LOCALPLAYER + offsets::m_vecOrigin);
}

Vec3 LocalPlayer::ViewAngles()
{
	return *(Vec3*)(CLIENTSTATE + offsets::dwClientState_ViewAngles);
}

int LocalPlayer::Health()
{
	return *(int*)(LOCALPLAYER + offsets::m_iHealth);
}

int LocalPlayer::TeamNum()
{
	return *(int*)(LOCALPLAYER + offsets::m_iTeamNum);
}

int LocalPlayer::Armor()
{
	return *(int*)(LOCALPLAYER + offsets::m_ArmorValue);
}

int LocalPlayer::Flags()
{
	return *(int*)(LOCALPLAYER + offsets::m_fFlags);
}

BOOL LocalPlayer::isDead()
{
	return (Health() <= 0);
}

BOOL LocalPlayer::CheckIfScoped()
{
	return *(bool*)(LOCALPLAYER + offsets::m_bIsScoped);
}