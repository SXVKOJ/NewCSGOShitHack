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
    float wear = 0.000001f;

    for (int i = 0; i < 8; i++)
    {
        int initWep = *(int*)(LocalPlayer + offsets::m_hActiveWeapon);

        int WeaponBase = *(int*)(Game.GetClient() + offsets::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

        if (WeaponBase != NULL)
        {
            short CurrentWeaponID = *(short*)(WeaponBase + offsets::m_iItemDefinitionIndex);

            if (CurrentWeaponID == weapon)
            {
                *(int*)(WeaponBase + offsets::m_iItemIDHigh) = 1;
                *(int*)(WeaponBase + offsets::m_nFallbackPaintKit) = tPainKit;
                *(float*)(WeaponBase + offsets::m_flFallbackWear) = wear;
                *(int*)(WeaponBase + offsets::m_nFallbackStatTrak) = 1337;

                FullForceUpdate();
            }
        }
    }
}