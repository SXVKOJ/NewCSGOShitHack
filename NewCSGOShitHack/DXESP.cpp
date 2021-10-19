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

        float boxHeight = abs(Head2Screen.y - Entity2Screen.y);
        float boxWidth = boxHeight / 2;

        int WindowWidth = Game.GetCurrentWindowSize().x;
        int WindowHeight = Game.GetCurrentWindowSize().y;

        DrawBox(Entity2Screen.x - boxWidth / 2, Head2Screen.y, boxWidth, boxHeight, config::esp::BoxWidth, D3DCOLOR_COLORVALUE(config::esp::DX_ESP[0], config::esp::DX_ESP[1], config::esp::DX_ESP[2], 1));
        if (config::esp::Lines)
            DrawLine(DXLines::Line, WindowWidth / 2, WindowHeight / 2, Entity2Screen.x, Entity2Screen.y, config::esp::LineWidth, true, D3DCOLOR_COLORVALUE(config::esp::DX_ESP[0], config::esp::DX_ESP[1], config::esp::DX_ESP[2], 1));

        if (config::esp::HP)
        {
            using namespace config::esp::health;

            DrawMessage(m_font,
                Entity2Screen.x + offset_x - (boxWidth / 2),
                Entity2Screen.y - boxHeight - 35 - offset_y,
                D3DCOLOR_COLORVALUE(color[0], color[1], color[2], 1),
                std::to_string(EntHealth).c_str());
        }

        if (config::esp::weapon::ShowWeapon)
        {
            using namespace config::esp::weapon;
            
            if (!custom_color)
                *color = *config::esp::DX_ESP;

            DrawMessage(weapon_font,
                Entity2Screen.x + offset_x,
                Entity2Screen.y - boxHeight - 35 - offset_y,
                D3DCOLOR_COLORVALUE(color[0], color[1], color[2], 1),
                Game.GetWeaponName((int)Game.GetEntityWeapon(Entity)).c_str());
        }

        int HealthBarOffsetX = 0;
        int HealthBarOffsetY = 0;
        
        if (config::esp::health::HealthBar || config::esp::health::ArmorBar)
        {
            if (config::esp::health::HealthBar && config::esp::health::ArmorBar &&
                config::esp::health::BarsPos == constVars.PosLeft)
                HealthBarOffsetX = 8;

            if (config::esp::health::HealthBar && config::esp::health::ArmorBar &&
                config::esp::health::BarsPos == constVars.PosTop)
                HealthBarOffsetY = 10;

            int EntityArmor = *(int*)(Entity + offsets::m_ArmorValue);

            int HealthBarX = Entity2Screen.x - (boxWidth / 2);
            int HealthBarY = Entity2Screen.y;
            
            if (config::esp::health::HealthBar)
            {
                if (config::esp::health::BarsPos == constVars.PosLeft)
                {
                    DrawLine(DXLines::HealthBarLine,
                        HealthBarX - HealthBarOffsetX - 8,
                        HealthBarY,
                        HealthBarX - HealthBarOffsetX - 8,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntHealth),
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }    
                else if (config::esp::health::BarsPos == constVars.PosTop)
                {
                    DrawLine(DXLines::HealthBarLine,
                        HealthBarX,
                        HealthBarY - boxHeight - HealthBarOffsetY,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntHealth),
                        HealthBarY - boxHeight - HealthBarOffsetY,
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
                else if (config::esp::health::BarsPos == constVars.PosRight)
                {
                    DrawLine(DXLines::HealthBarLine,
                        HealthBarX + boxWidth + 8,
                        HealthBarY,
                        HealthBarX + boxWidth + 8,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntHealth),
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
                else if (config::esp::health::BarsPos == constVars.PosBottom)
                {
                    DrawLine(DXLines::HealthBarLine,
                        HealthBarX,
                        HealthBarY,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntHealth),
                        HealthBarY,
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
            }
            
            if (config::esp::health::ArmorBar)
            {
                if (config::esp::health::BarsPos == constVars.PosLeft)
                {
                    DrawLine(DXLines::ArmorBarLine,
                        HealthBarX - 8,
                        HealthBarY,
                        HealthBarX - 8,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntityArmor),
                        6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
                }
                else if (config::esp::health::BarsPos == constVars.PosTop)
                {
                    DrawLine(DXLines::ArmorBarLine,
                        HealthBarX,
                        HealthBarY - boxHeight,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntityArmor),
                        HealthBarY - boxHeight,
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
                else if (config::esp::health::BarsPos == constVars.PosRight)
                {
                    DrawLine(DXLines::ArmorBarLine,
                        HealthBarX + boxWidth,
                        HealthBarY,
                        HealthBarX + boxWidth,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntityArmor),
                        6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
                }
                else if (config::esp::health::BarsPos == constVars.PosBottom)
                {
                    DrawLine(DXLines::ArmorBarLine,
                        HealthBarX,
                        HealthBarY + 8,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntityArmor),
                        HealthBarY + 8,
                        6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
                }
            }
        }
    }
}