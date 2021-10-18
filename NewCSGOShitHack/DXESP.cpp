#include "includes.h"

void HACK::DXESPThread()
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

        DrawBox(Entity2Screen.x - boxWidth / 2, Head2Screen.y, boxWidth, boxHeight, config::esp::BoxWidth, D3DCOLOR_COLORVALUE(config::esp::DX_ESP[0], config::esp::DX_ESP[1], config::esp::DX_ESP[2], 1));
        if (config::esp::Lines)
            DrawLine(DXLines::Line, WindowWidth / 2, WindowHeight / 2, Entity2Screen.x, Entity2Screen.y, config::esp::LineWidth, true, D3DCOLOR_COLORVALUE(config::esp::DX_ESP[0], config::esp::DX_ESP[1], config::esp::DX_ESP[2], 1));

        if (config::esp::HP)
        {
            using namespace config::esp::health;

            if (!custom_color)
                *color = *config::esp::DX_ESP;

            DrawMessage(m_font, Entity2Screen.x + offset_x - (boxWidth / 2), Entity2Screen.y - boxHeight - 35 - offset_y, D3DCOLOR_COLORVALUE(color[0], color[1], color[2], 1), std::to_string(EntHealth).c_str());
        }

        if (config::esp::weapon::ShowWeapon)
        {
            using namespace config::esp::weapon;
            
            if (!custom_color)
                *color = *config::esp::DX_ESP;

            DrawMessage(weapon_font, Entity2Screen.x + offset_x, Entity2Screen.y - boxHeight - 35 - offset_y, D3DCOLOR_COLORVALUE(color[0], color[1], color[2], 1), Game.GetWeaponName((int)Game.GetEntityWeapon(Entity)).c_str());
        }

        int HealthBarOffsetX = 0;

        if (config::esp::health::HealthBar || config::esp::health::ArmorBar)
        {
            if (config::esp::health::HealthBar && config::esp::health::ArmorBar)
                HealthBarOffsetX = 5;

            int EntityArmor = *(int*)(Entity + offsets::m_ArmorValue);

            int HealthBarX = Entity2Screen.x - (boxWidth / 2);
            int HealthBarY = Entity2Screen.y;
            
            if (config::esp::health::HealthBar)
            {
                DrawLine(DXLines::HealthBarLine, HealthBarX - HealthBarOffsetX - 8, HealthBarY, HealthBarX - HealthBarOffsetX - 8, HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntHealth), 6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
            }
            
            if (config::esp::health::ArmorBar)
            {
                DrawLine(DXLines::ArmorBarLine, HealthBarX - 8, HealthBarY, HealthBarX - 8, HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntityArmor), 6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
            }
        }
    }
}