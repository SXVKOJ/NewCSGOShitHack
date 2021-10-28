#include "includes.h"

void HACK::ESPDrawBonesThread()
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

        DrawBones(DXLines::BodyLine, Entity, std::vector<int> {3, 4, 5, 6, 7, 8}, config::esp::LineWidth); // Body
        DrawBones(DXLines::rLegLine, Entity, std::vector<int> {3, 70, 71, 72}, config::esp::LineWidth); // Right Leg
        DrawBones(DXLines::lLegLine, Entity, std::vector<int> {3, 77, 78, 79}, config::esp::LineWidth); // Left Leg
        DrawBones(DXLines::lArmLine, Entity, std::vector<int> {7, 11, 12, 13}, config::esp::LineWidth); // Left Arm
        DrawBones(DXLines::rArmLine, Entity, std::vector<int> {7, 41, 42, 43}, config::esp::LineWidth); // Right Arm
	}
}