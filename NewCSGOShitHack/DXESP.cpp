#include "includes.h"

void HACK::DXESPThread(LPDIRECT3DDEVICE9& pDevice)
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

        Vec3 EntityPos = *(Vec3*)(Entity + offsets::m_vecOrigin);
        Vec3 Entity2Screen;

        Vec3 EntityHead = Game.GetPlayerBonePos(Entity, 8);
        Vec3 Head2Screen;

        memcpy(&Game.ViewMatrix, (PBYTE*)(Game.GetClient() + offsets::dwViewMatrix), sizeof(Game.ViewMatrix));

        Game.WorldToScreen(EntityPos, Entity2Screen);
        Game.WorldToScreen(EntityHead, Head2Screen);

        int boxHeight = abs(Head2Screen.y - Entity2Screen.y);
        int boxWidth = boxHeight / 2;

        int WindowWidth = Game.GetCurrentWindowSize().x;
        int WindowHeight = Game.GetCurrentWindowSize().y;

        DrawBox(Entity2Screen.x - boxWidth / 2, Head2Screen.y, boxWidth, boxHeight, BoxWidth, D3DCOLOR_COLORVALUE(DX_ESP[0], DX_ESP[1], DX_ESP[2], 1), pDevice);
        DrawLine(WindowWidth / 2, WindowHeight / 2, Entity2Screen.x, Entity2Screen.y, LineWidth, true, D3DCOLOR_COLORVALUE(DX_ESP[0], DX_ESP[1], DX_ESP[2], 1), pDevice);
    }
}