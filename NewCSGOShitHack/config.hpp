#pragma once

static struct CONFIG
{
	int FOV = 90;
	
	bool Bhop = true;
	bool HealthTreshold = true;
	bool TriggerBot = true;
	bool NeonWallHack = true;
	bool AimBot = true;
	bool RecoilControlSystem = true;
	bool RadarHack = true;

	int HealthTresholdVal = 33;
	int BhopDelay = 17;
	int TriggerBotDelay = 45;

	int AimBotHotKey = 18; // VK_ALT

	float LC_NEONESP[3] = { 0, 1, 1 };
	float ET_NEONESP[3] = { 1, 0, 1 };
} Config;