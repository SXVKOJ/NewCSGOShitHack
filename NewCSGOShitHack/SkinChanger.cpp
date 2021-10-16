#include "includes.h"

bool HACK::IsKnifeWeapon()
{
    short wepID = Game.GetCurrentWeapon();

    return false;
}

void HACK::FullForceUpdate()
{
    DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);
    *(int*)(ClientState + offsets::clientstate_delta_ticks) = -1;
}

void HACK::ChangeSkin(short weapon, int paint)
{
    DWORD LocalPlayer = Game.GetLocalPlayer();

    int tWeapon = weapon;
    int tPainKit = paint;
    float wear = 0.000001f;

    for (int i = 0; i < 8; i++)
    {
        int WeaponBase = *(int*)(LocalPlayer + offsets::m_hActiveWeapon + i * 0x4) & 0xFFF;

        WeaponBase = *(int*)(Game.GetClient() + offsets::dwEntityList + (WeaponBase - 1) * 0x10);

        if (WeaponBase != NULL)
        {           
            short CurrentWeaponID = Game.GetCurrentWeapon();

            if (CurrentWeaponID != weapon)
            {
                if (*(int*)(WeaponBase + offsets::m_iItemIDHigh) != -1)
                    *(int*)(WeaponBase + offsets::m_iItemIDHigh) = -1;

                *(int*)(WeaponBase + offsets::m_OriginalOwnerXuidLow) = 0;
                *(int*)(WeaponBase + offsets::m_OriginalOwnerXuidHigh) = 0;
                *(int*)(WeaponBase + offsets::m_nFallbackPaintKit) = tPainKit;
                *(int*)(WeaponBase + offsets::m_nFallbackSeed) = 0;
                *(int*)(WeaponBase + offsets::m_nFallbackStatTrak) = 1337;
                *(float*)(WeaponBase + offsets::m_flFallbackWear) = wear;
                *(int*)(WeaponBase + offsets::m_iEntityQuality) = 9;
            }
        }
    }
}