#include "includes.h"

int UserCFG[526];

bool HACK::IsKnifeWeapon(short wepID)
{
    return (wepID == WEAPON_KNIFE_T         || 
            wepID == WEAPON_KNIFE_CT        ||
            wepID == WEAPON_KNIFE_KARAM     ||
            wepID == WEAPON_KNIFE_BAYONET   ||
            wepID == WEAPON_KNIFE_CLASSIC   ||
            wepID == WEAPON_KNIFE_FLIP      ||
            wepID == WEAPON_KNIFE_GUT       ||
            wepID == WEAPON_KNIFE_M9        ||
            wepID == WEAPON_KNIFE_HUNTSMAN  ||
            wepID == WEAPON_KNIFE_FALCHION  ||
            wepID == WEAPON_KNIFE_BOWIE     ||
            wepID == WEAPON_KNIFE_BUTTERFLY ||
            wepID == WEAPON_KNIFE_DAGGERS   ||
            wepID == WEAPON_KNIFE_PARACORD  ||
            wepID == WEAPON_KNIFE_SURVIVAL  ||
            wepID == WEAPON_KNIFE_URSUS     ||
            wepID == WEAPON_KNIFE_NAVAJA    ||
            wepID == WEAPON_KNIFE_NOMAD     ||
            wepID == WEAPON_KNIFE_STILETTO  ||
            wepID == WEAPON_KNIFE_TALON     ||
            wepID == WEAPON_KNIFE_SKELETON);
}

std::string KnifeTypeToName()
{
    switch (config::SkinChanger::KnifeType)
    {
    case 1:
        return "KNIFE_BAYONET";
    case 2:
        return "KNIFE_FLIP";
    case 3:
        return "KNIFE_GUT";
    case 4:
        return "KNIFE_KARAMBIT";
    case 5:
        return "KNIFE_M9BAYONET";
    case 6:
        return "KNIFE_TACTICAL";
    case 7:
        return "KNIFE_FALCHION";
    case 8:
        return "KNIFE_BOWIE";
    case 9:
        return "KNIFE_BUTTERFLY";
    case 10:
        return "KNIFE_SHADOWDAGGERS";
    case 0:
        return "Default";
    }
}

int GetKnifeViewModelIndex(int Type)
{
    /*
     '(m_iViewModelIndex, m_iWorldModelIndex, m_iItemDefinitionIndex)
        '(379, 380, 500), // KNIFE_BAYONET
        '(382, 383, 505), // KNIFE_FLIP
        '(385, 386, 506), // KNIFE_GUT
        '(388, 389, 507), // KNIFE_KARAMBIT
        '(391, 392, 508), // KNIFE_M9BAYONET
        '(394, 395, 509), // KNIFE_TACTICAL
        '(397, 398, 510), // KNIFE_FALCHION
        '(400, 401, 511), // KNIFE_BOWIE
        '(403, 404, 515), // KNIFE_BUTTERFLY
        '(406, 407, 516), // KNIFE_SHADOWDAGGERS */
    
    return 376 + (Type * 3);
}

int GetKnifeWorldModelIndex(int Type)
{
    return GetKnifeViewModelIndex(Type) + 1;
}

void HACK::FullForceUpdate()
{
    DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);
    *(int*)(ClientState + offsets::clientstate_delta_ticks) = -1;
}

int LastWeaponID = 0;
int WeaponIndex = 0;

void HACK::SkinChangerThread()
{
    DWORD LocalPlayer = Game.GetLocalPlayer();
    DWORD ClientState = *(DWORD*)(Game.GetEngine() + offsets::dwClientState);

    float wear = 0.000001f;

    for (int i = 1; i < 120; i++)
    {
        if (UserCFG[i] == 0)
            continue;  

        int Weapon = i;
        int PaintKit = UserCFG[i];

        if (Game.GetCurrentWeapon() == Weapon)
        {
            int WeaponBase = NULL;

            // Get Weapon index
            for (int j = 0; j < 8; j++)
            {
                WeaponBase = *(int*)(LocalPlayer + offsets::m_hActiveWeapon + j * 0x4) & 0xFFF;
                WeaponBase = *(int*)(Game.GetClient() + offsets::dwEntityList + (WeaponBase - 1) * 0x10);

                if (WeaponBase != NULL)
                {
                    short CurrentWeaponID = *(short*)(WeaponBase + offsets::m_iItemDefinitionIndex);

                    if (CurrentWeaponID == Weapon)
                        WeaponIndex = j;
                }
            }

            if (WeaponBase != NULL)
            {
                WeaponBase = *(int*)(LocalPlayer + offsets::m_hActiveWeapon + WeaponIndex * 0x4) & 0xFFF;
                WeaponBase = *(int*)(Game.GetClient() + offsets::dwEntityList + (WeaponBase - 1) * 0x10);

                int AccountID = *(int*)(WeaponBase + offsets::m_OriginalOwnerXuidLow);
                short CurrentWeaponID = *(short*)(WeaponBase + offsets::m_iItemDefinitionIndex);

                if (!IsKnifeWeapon(CurrentWeaponID))
                {
                    *(int*)(WeaponBase + offsets::m_nFallbackPaintKit) = PaintKit;
                    *(int*)(WeaponBase + offsets::m_nFallbackSeed) = 0;
                    *(float*)(WeaponBase + offsets::m_flFallbackWear) = wear;
                    *(int*)(WeaponBase + offsets::m_nFallbackStatTrak) = config::SkinChanger::StatTrackVal;
                    *(int*)(WeaponBase + offsets::m_iAccountID) = AccountID;
                    *(int*)(WeaponBase + offsets::m_iEntityQuality) = 6;
                    *(int*)(WeaponBase + offsets::m_iItemIDHigh) = -1;
                }
                else
                {
                    if (config::SkinChanger::KnifeType != 0)
                    {
                        *(int*)(WeaponBase + offsets::m_iEntityQuality) = 3;
                        *(int*)(WeaponBase + offsets::m_nViewModelIndex) = GetKnifeViewModelIndex(config::SkinChanger::KnifeType);
                        *(int*)(WeaponBase + offsets::m_iWorldModelIndex) = GetKnifeWorldModelIndex(config::SkinChanger::KnifeType);
                        *(int*)(WeaponBase + offsets::m_nModelIndex) = GetKnifeWorldModelIndex(config::SkinChanger::KnifeType);
                    }                   
                }

                if (LastWeaponID != CurrentWeaponID)
                {
                    Hack.FullForceUpdate();
                    LastWeaponID = CurrentWeaponID;
                }
            }            
        }            
    }
}