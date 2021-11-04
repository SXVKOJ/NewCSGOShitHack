#include "includes.h"

static Vec3 WindowSize = Engine.GetCurrentWindowSize();
static int WindowWidth = WindowSize.x;
static int WindowHeight = WindowSize.y;
static int mWindowX = WindowWidth / 2;
static int mWindowY = WindowHeight / 2;

void HACK::DXESPThread()
{
    for (int i = 1; i < 64; i++)
    {
        uintptr_t Entity = *(uintptr_t*)(CLIENT + offsets::dwEntityList + i * cVars::PlayerStructSize);

        if (!Entity)
            continue;

        int EntDormant = *(int*)(Entity + offsets::m_bDormant);

        if (EntDormant)
            continue;

        int EntHealth = *(int*)(Entity + offsets::m_iHealth);

        if (EntHealth <= 0)
            continue;

        int EntTeam = *(int*)(Entity + offsets::m_iTeamNum);

        if (EntTeam == lPlayer.TeamNum())
            continue;

        Vec3 EntityPos = *(Vec3*)(Entity + offsets::m_vecOrigin);
        Vec3 Entity2Screen;

        Vec3 EntityHead = Engine.GetPlayerBonePos(Entity, 8);
        Vec3 Head2Screen;

        memcpy(&Engine.ViewMatrix, (PBYTE*)(CLIENT + offsets::dwViewMatrix), sizeof(Engine.ViewMatrix));
        Engine.WorldToScreen(EntityPos, Entity2Screen);
        Engine.WorldToScreen(EntityHead, Head2Screen);

        float boxHeight = abs(Head2Screen.y - Entity2Screen.y);
        float boxWidth = boxHeight / 2;

        mDevice.DrawBox(Entity2Screen.x - boxWidth / 2, Head2Screen.y, boxWidth, boxHeight, config::esp::box::Width, D3DCOLOR_COLORVALUE(config::esp::colors::ET_ESP[0],
                                                                                                                                         config::esp::colors::ET_ESP[1],
                                                                                                                                         config::esp::colors::ET_ESP[2], 1));
        if (config::esp::Lines)
            mDevice.DrawLine(mDevice.espLine, mWindowX, mWindowY, Entity2Screen.x, Entity2Screen.y, config::esp::line::Width, true, D3DCOLOR_COLORVALUE(config::esp::colors::ET_ESP[0],
                                                                                                                                                        config::esp::colors::ET_ESP[1],                                                                                                                                                 config::esp::colors::ET_ESP[2], 1));

        if (config::esp::HealthBar)
        {
            using namespace config::esp::bar;

            mDevice.DrawMessage(mDevice.health_font,
                Entity2Screen.x + offset_x - (boxWidth / 2),
                Entity2Screen.y - boxHeight - 35 - offset_y,
                D3DCOLOR_COLORVALUE(config::esp::colors::ET_ESP[0],
                                    config::esp::colors::ET_ESP[1],
                                    config::esp::colors::ET_ESP[2], 1),
                std::to_string(EntHealth).c_str());
        }

        if (config::esp::ShowWeapon)
        {
            using namespace config::esp::weapon;

            mDevice.DrawMessage(mDevice.weapon_font,
                Entity2Screen.x + offset_x,
                Entity2Screen.y - boxHeight - 35 - offset_y,
                D3DCOLOR_COLORVALUE(config::esp::colors::ET_ESP[0],
                                    config::esp::colors::ET_ESP[1],
                                    config::esp::colors::ET_ESP[2], 1),
                Engine.GetWeaponName((int)Engine.GetEntityWeapon(Entity)).c_str());
        }

        int HealthBarOffsetX = 0;
        int HealthBarOffsetY = 0;
        
        if (config::esp::HealthBar || config::esp::ArmorBar)
        {
            if (config::esp::bar::BarsPos == cVars::WallHack::posLeft &&
                (config::esp::HealthBar && config::esp::ArmorBar))
                HealthBarOffsetX = 8;

            if (config::esp::bar::BarsPos == cVars::WallHack::posTop &&
                (config::esp::HealthBar && config::esp::ArmorBar))
                HealthBarOffsetY = 10;

            int EntityArmor = *(int*)(Entity + offsets::m_ArmorValue);

            int HealthBarX = Entity2Screen.x - (boxWidth / 2);
            int HealthBarY = Entity2Screen.y;
            
            if (config::esp::HealthBar)
            {
                if (config::esp::bar::BarsPos == cVars::WallHack::posLeft)
                {
                    mDevice.DrawLine(mDevice.HealthBarLine,
                        HealthBarX - HealthBarOffsetX - 8,
                        HealthBarY,
                        HealthBarX - HealthBarOffsetX - 8,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntHealth),
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }    
                else if (config::esp::bar::BarsPos == cVars::WallHack::posTop)
                {
                    mDevice.DrawLine(mDevice.HealthBarLine,
                        HealthBarX,
                        HealthBarY - boxHeight - HealthBarOffsetY,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntHealth),
                        HealthBarY - boxHeight - HealthBarOffsetY,
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
                else if (config::esp::bar::BarsPos == cVars::WallHack::posRight)
                {
                    mDevice.DrawLine(mDevice.HealthBarLine,
                        HealthBarX + boxWidth + 8,
                        HealthBarY,
                        HealthBarX + boxWidth + 8,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntHealth),
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
                else if (config::esp::bar::BarsPos == cVars::WallHack::posBottom)
                {
                    mDevice.DrawLine(mDevice.HealthBarLine,
                        HealthBarX,
                        HealthBarY,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntHealth),
                        HealthBarY,
                        6, true, D3DCOLOR_COLORVALUE(1, 0, 0, 1));
                }
            }
            
            if (config::esp::ArmorBar)
            {
                if (config::esp::bar::BarsPos == cVars::WallHack::posLeft)
                {
                    mDevice.DrawLine(mDevice.ArmorBarLine,
                        HealthBarX - 8,
                        HealthBarY,
                        HealthBarX - 8,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntityArmor),
                        6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
                }
                else if (config::esp::bar::BarsPos == cVars::WallHack::posTop)
                {
                    mDevice.DrawLine(mDevice.ArmorBarLine,
                        HealthBarX,
                        HealthBarY - boxHeight,
                        HealthBarX - (((HealthBarX - (HealthBarX + boxWidth)) / 100) * EntityArmor),
                        HealthBarY - boxHeight,
                        6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
                }
                else if (config::esp::bar::BarsPos == cVars::WallHack::posRight)
                {
                    mDevice.DrawLine(mDevice.ArmorBarLine,
                        HealthBarX + boxWidth,
                        HealthBarY,
                        HealthBarX + boxWidth,
                        HealthBarY + (((Head2Screen.y - Entity2Screen.y) / 100) * EntityArmor),
                        6, true, D3DCOLOR_COLORVALUE(0, 1, 0, 1));
                }
                else if (config::esp::bar::BarsPos == cVars::WallHack::posBottom)
                {
                    mDevice.DrawLine(mDevice.ArmorBarLine,
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