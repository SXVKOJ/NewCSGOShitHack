#include "includes.h"

void HACK::FullForceUpdate()
{
    DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);
    *(int*)(ClientState + offsets::clientstate_delta_ticks) = -1;
}

void HACK::ChangeSkin(int weapon, int paint)
{
    DWORD LocalPlayer = Game.GetLocalPlayer();

    int tWeapon = weapon;
    int tPainKit = paint;
    float wear = 0.001f;

    for (int i = 0; i < 8; i++)
    {
        int cWep = *(int*)(LocalPlayer + offsets::m_hMyWeapons + i * 0x4) & 0xfff;
        cWep = *(int*)(Game.GetClient() + offsets::dwEntityList + (cWep - 1) * 0x10);

        if (*(int*)(cWep + offsets::m_nFallbackPaintKit) == tPainKit)
            return;

        if (cWep != 0)
        {
            short cWepID = *(short*)(cWep + offsets::m_iItemDefinitionIndex);

            if (cWepID == weapon)
            {
                *(int*)(cWep + offsets::m_iItemIDHigh) = -1;
                *(int*)(cWep + offsets::m_nFallbackPaintKit) = tPainKit;
                *(float*)(cWep + offsets::m_flFallbackWear) = wear;
                *(int*)(cWep + offsets::m_OriginalOwnerXuidLow) = 0;
                *(int*)(cWep + offsets::m_OriginalOwnerXuidHigh) = 0;
                *(int*)(cWep + offsets::m_nFallbackStatTrak) = 1337;
                *(int*)(cWep + offsets::m_iEntityQuality) = 3;
            }
        }
    }
}