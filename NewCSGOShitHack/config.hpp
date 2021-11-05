#pragma once

namespace hackstate
{
	extern bool ImGui_Init;
	extern bool ImGui_Attached;
	extern bool AimBotActive;
	extern bool MenuActive;
}

namespace config
{
	namespace hack
	{
		extern int FOV;
		extern bool Bhop;
		extern bool TriggerBot;
		extern bool NeonWallHack;
		extern bool AimBot;
		extern bool RecoilControlSystem;
		extern bool RadarHack;
		extern bool NoFlash;
		extern bool WallHackESP;
		extern bool SpinBot;
		extern bool AimingAssistance;
		extern bool SmoothAimBot;
		extern bool ThirdPersonView;
		extern bool TPSActive;
		extern bool TriggerBotInAimBot;
		extern bool SkinChanger;
	}

	namespace aimbot
	{
		extern int TriggerBotCooldown;
		extern int SmoothVal;
		extern int SpinBotSpeed;
		extern int TargetBonePos;
		extern int LegitDiff;
		extern bool Compensation;
		extern int CompensationVal;
		extern bool LegitMode;
		
		extern int SniperWeaponTriggerBotCooldown;
	}

	namespace View
	{
		extern float offset_x;
		extern float offset_y;
		extern float offset_z;

		extern bool custom;
	}
	
	namespace SkinChanger
	{
		extern int CurrentSkinID;
		extern int CurrentWeaponID;

		extern bool CustomName;
		extern char* szCustomName;
		extern bool StatTrack;
		extern int StatTrackVal;

		extern int KnifeType;
		extern float wear;
	}
	
	namespace HotKeys
	{
		extern int AimBot;   // VK_ALT
		extern int End;     // VK_END
		extern int Menu;   // VK_HOME	
	}

	namespace esp
	{
		namespace box
		{
			extern int Width;
		}
		namespace line
		{
			extern int Width;
		}
		namespace colors
		{
			extern float LT_GLOW[3];
			extern float ET_GLOW[3];

			extern float ET_ESP[3];
			extern float HealthColor[3];
		}

		extern bool HealthBar;
		extern bool ArmorBar;
		extern bool Boxes;
		extern bool Lines;
		extern bool ShowNames;
		extern bool ShowWeapon;
		extern bool HealthNum;

		namespace bar
		{
			extern int offset_x;
			extern int offset_y;

			extern int BarsPos;
		}

		namespace weapon
		{
			extern int offset_x;
			extern int offset_y;

			extern bool custom_color;
			extern float color[3];
		}
	}
}