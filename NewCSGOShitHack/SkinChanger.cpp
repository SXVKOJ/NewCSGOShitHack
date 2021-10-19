#include "includes.h"

int UserCFG[526];

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

void HACK::SkinChangerThread()
{
    DWORD LocalPlayer = Game.GetLocalPlayer();

    float wear = 0.000001f;

    for (int j = 0; j < 526; j++)
    {
        if (UserCFG[j] == 0)
            continue;

        int tWeapon = j;
        int tPainKit = UserCFG[j];

        for (int i = 0; i < 8; i++)
        {
            int WeaponBase = *(int*)(LocalPlayer + offsets::m_hActiveWeapon + i * 0x4) & 0xFFF;

            WeaponBase = *(int*)(Game.GetClient() + offsets::dwEntityList + (WeaponBase - 1) * 0x10);

            if (WeaponBase != NULL)
            {
                short CurrentWeaponID = *(short*)(WeaponBase + offsets::m_iItemDefinitionIndex);

                if (CurrentWeaponID == tWeapon)
                {
                    *(int*)(WeaponBase + offsets::m_iItemIDHigh) = -1;
                    *(int*)(WeaponBase + offsets::m_nFallbackPaintKit) = tPainKit;
                    *(float*)(WeaponBase + offsets::m_flFallbackWear) = wear;
                    *(int*)(WeaponBase + offsets::m_nFallbackSeed) = 0;
                }
            }
        }
    }
}