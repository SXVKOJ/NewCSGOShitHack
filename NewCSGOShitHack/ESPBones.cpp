#include "includes.h"

void HACK::ESPDrawBonesThread(LPDIRECT3DDEVICE9& pDevice)
{
    DWORD LocalPlayer = *(DWORD*)(Game.GetClient() + offsets::dwLocalPlayer);
    int LocalPlayerTeam = *(int*)(LocalPlayer + offsets::m_iTeamNum);

	for (int i = 1; i < 64; i++)
	{
        DWORD Entity = *(DWORD*)(Game.GetClient() + offsets::dwEntityList + i * constVars.PlayerStructSize);

        if (!Entity)
            continue;

        int EntDormant = *(int*)(Entity + offsets::m_bDormant);

        if (EntDormant)
            continue;

        int EntHealth = *(int*)(Entity + offsets::m_iHealth);

        if (EntHealth <= 0)
            continue;

        int EntTeam = *(int*)(Entity + offsets::m_iTeamNum);

        if (EntTeam == LocalPlayerTeam)
            continue;

        memcpy(&Game.ViewMatrix, (PBYTE*)(Game.GetClient() + offsets::dwViewMatrix), sizeof(Game.ViewMatrix));
        DrawBones(BodyLine, Entity, std::vector<int>{3, 4, 5, 6, 7, 8}, config::LineWidth, pDevice); // Body
        DrawBones(rLegLine, Entity, std::vector<int>{3, 70, 71, 72}, config::LineWidth, pDevice); // Right Leg
        DrawBones(lLegLine, Entity, std::vector<int>{3, 77, 78, 79}, config::LineWidth, pDevice); // Left Leg
        DrawBones(lArmLine, Entity, std::vector<int>{7, 11, 12, 13}, config::LineWidth, pDevice); // Left Arm
        DrawBones(rArmLine, Entity, std::vector<int>{7, 41, 42, 43}, config::LineWidth, pDevice); // Right Arm
	}
}