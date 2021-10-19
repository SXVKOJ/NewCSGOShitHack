#pragma once

namespace config
{
	extern int FOV;
	extern int SmoothStep;
	extern int SpinBotSpeed;
	extern int TargetBonePos;

	extern bool console;
	extern bool ImGui_Init;
	extern bool ImGui_Attached;
	extern bool AimBotActive;

	extern bool Bhop;
	extern bool HealthTreshold;
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
	extern bool AimLegitMode;
	extern bool TriggerBotInAimBot;

	extern int HealthTresholdVal;
	extern int BhopDelay;
	extern int TriggerBotCooldown;
	extern int MainThreadDelay;
	extern int SilentAimSmooth;
	extern int LegitAimBotDiff;

	extern bool FPSMode;

	namespace Aim
	{
		extern bool Compensation;
		extern int CompensationVal;
		extern int CurrentWeaponID;
	}

	extern bool MenuActive;

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
	}
	
	namespace HotKeys
	{
		extern int AimBot;   // VK_ALT
		extern int End;     // VK_END
		extern int Menu;   // VK_HOME	
	}

	namespace esp
	{
		extern int BoxWidth;
		extern int LineWidth;

		extern float LT_NEONESP[3];
		extern float ET_NEONESP[3];

		extern float DX_ESP[3];

		extern bool HP;
		extern bool ESPBones;
		extern bool Lines;

		namespace health
		{
			extern int offset_x;
			extern int offset_y;

			extern bool custom_color;
			extern float color[3];

			extern bool HealthBar;
			extern bool ArmorBar;

			extern int BarsPos;
		}

		namespace weapon
		{
			extern bool ShowWeapon;
			extern int offset_x;
			extern int offset_y;

			extern bool custom_color;
			extern float color[3];
		}
	}
}