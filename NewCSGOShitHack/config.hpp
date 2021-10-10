#pragma once

static struct CONFIG
{
	int FOV = 90;
	
	bool console = false;
	bool ImGui_Init = false;
	bool ImGui_Attached = false;
	bool AimBotActive = false;
	bool MenuActive = false;

	bool Bhop = true;
	bool HealthTreshold = true;
	bool TriggerBot = true;
	bool NeonWallHack = true;
	bool AimBot = true;
	bool RecoilControlSystem = true;
	bool RadarHack = true;
	bool NoFlash = true;
	bool WallHackESP = true;

	int HealthTresholdVal = 33;
	int BhopDelay = 17;
	int TriggerBotDelay = 65;

	int AimBotHotKey = 18;   // VK_ALT
	int EndHotKey = 0x23;   // VK_END
	int MenuHotKey = 0x24; // VK_HOME

	float LT_NEONESP[3] = { 0, 1, 1 };
	float ET_NEONESP[3] = { 1, 0, 1 };

	float DX_ESP[3] = { 1, 0, 1 };
} Config;