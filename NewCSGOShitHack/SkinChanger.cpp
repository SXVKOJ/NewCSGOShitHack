#include "includes.h"

void HACK::FullForceUpdate()
{
    uintptr_t ClientState = CLIENTSTATE;
    *(int*)(ClientState + offsets::clientstate_delta_ticks) = -1;
}

static int LastWeaponID = 0;
static int WeaponIndex = 0;

void HACK::SkinChangerThread()
{
    float wear = config::SkinChanger::wear;

    for (int i = 1; i < 69; i++)
    {
        if (Engine.SkinChangerCFG[i] == 0)
            continue;  

        int Weapon = i;
        int PaintKit = Engine.SkinChangerCFG[i];

        if (Weapon == lPlayer.GetCurrentWeapon())
        {
            int WeaponBase = NULL;

            // Get Weapon index
            for (int j = 0; j < 8; j++)
            {
                WeaponBase = *(int*)(LOCALPLAYER + offsets::m_hActiveWeapon + j * 0x4) & 0xFFF;
                WeaponBase = *(int*)(CLIENT + offsets::dwEntityList + (WeaponBase - 1) * 0x10);

                if (WeaponBase != NULL)
                {
                    short CurrentWeaponID = *(short*)(WeaponBase + offsets::m_iItemDefinitionIndex);

                    if (CurrentWeaponID == Weapon)
                        WeaponIndex = j;
                }
            }

            if (WeaponBase != NULL)
            {
                WeaponBase = *(int*)(LOCALPLAYER + offsets::m_hActiveWeapon + WeaponIndex * 0x4) & 0xFFF;
                WeaponBase = *(int*)(CLIENT + offsets::dwEntityList + (WeaponBase - 1) * 0x10);

                int AccountID = *(int*)(WeaponBase + offsets::m_OriginalOwnerXuidLow);
                short CurrentWeaponID = *(short*)(WeaponBase + offsets::m_iItemDefinitionIndex);

                *(int*)(WeaponBase + offsets::m_nFallbackPaintKit) = PaintKit;
                *(int*)(WeaponBase + offsets::m_nFallbackSeed) = 0;
                *(float*)(WeaponBase + offsets::m_flFallbackWear) = wear;
                *(int*)(WeaponBase + offsets::m_nFallbackStatTrak) = config::SkinChanger::StatTrackVal;
                *(int*)(WeaponBase + offsets::m_iAccountID) = AccountID;
                *(int*)(WeaponBase + offsets::m_iEntityQuality) = 3;
                *(int*)(WeaponBase + offsets::m_iItemIDHigh) = -1;

                if (LastWeaponID != CurrentWeaponID)
                {
                    Hack.FullForceUpdate();
                    LastWeaponID = CurrentWeaponID;
                }
            }            
        }            
    }
}