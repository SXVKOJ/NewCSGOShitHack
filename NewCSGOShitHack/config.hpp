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
	
	extern int CurrentSkinID;
	extern int AimBotHotKey;   // VK_ALT
	extern int EndHotKey;     // VK_END
	extern int MenuHotKey;   // VK_HOME
	extern bool MenuActive;

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

			extern int HealthBarWidth;
			extern int ArmorBarWidth;
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