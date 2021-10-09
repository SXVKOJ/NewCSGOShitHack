#include "includes.h"

DWORD GAME::GetClient()
{
	return (DWORD)GetModuleHandle("client.dll");
}

DWORD GAME::GetEngine()
{
	return (DWORD)GetModuleHandle("engine.dll");
}

DWORD GAME::GetLocalPlayer()
{
	return *(DWORD*)(this->GetClient() + offsets::dwLocalPlayer);
}

void GAME::PlayerShoot()
{
	DWORD client = this->GetClient();

	*(int*)(client + offsets::dwForceAttack) = constVars.FlagsActive;
	Sleep(Config.TriggerBotDelay);
	*(int*)(client + offsets::dwForceAttack) = constVars.FlagsOFF;
}

void GAME::PlayerJump()
{
	DWORD client = this->GetClient();

	*(int*)(client + offsets::dwForceJump) = constVars.FlagsActive;
	Sleep(Config.BhopDelay);
	*(int*)(client + offsets::dwForceJump) = constVars.FlagsOFF;
}

Vec3 GAME::GetPlayerBonePos(DWORD Entity, int index)
{
	DWORD BoneMatrix = *(DWORD*)(Entity + offsets::m_dwBoneMatrix);

	static Vec3 Bone;

	Bone.x = *(float*)(BoneMatrix + 0x30 * index + 0xC);
	Bone.y = *(float*)(BoneMatrix + 0x30 * index + 0x1C);
	Bone.z = *(float*)(BoneMatrix + 0x30 * index + 0x2C);

	return Bone;
}