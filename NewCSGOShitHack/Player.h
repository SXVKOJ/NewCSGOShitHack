#include <Windows.h>
#include "constvars.hpp"

#define LOCALPLAYER *(uintptr_t*)(CLIENT + offsets::dwLocalPlayer)
#define LOCALPLAYERADDRESS = (CLIENT + offsets::dwLocalPlayer)

static class LocalPlayer
{
public:
	VOID Shoot(uintptr_t& Entity);

	VOID Jump();

	VOID SetViewAngles(Vec3 dest);

	short GetCurrentWeapon();

	Vec3 Velocity();

	Vec3 Position();

	Vec3 ViewAngles();
	
	int Health();

	int TeamNum();

	int Armor();

	int Flags();

	BOOL isDead();

	BOOL CheckIfScoped();
} lPlayer;