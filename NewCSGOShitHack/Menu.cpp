#include "includes.h"

void HACK::MenuThread()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");
	ImGui::SetWindowSize(ImVec2(522, 646), 0);

	ImGui::Separator();
	ImGui::SliderInt("FOV Slider", &Config.FOV, 90, 160);
	ImGui::SliderInt("SpinBot Speed", &Config.SpinBotSpeed, 0, 200);
	ImGui::SliderInt("Trigger Bot Delay", &Config.TriggerBotDelay, 20, 200);
	ImGui::SliderInt("Bhop Delay", &Config.BhopDelay, 10, 30);
	ImGui::SliderInt("Default Delay", &Config.Delay, 1, 5);
	ImGui::SliderInt("Health Treshold value (Aimbot)", &Config.HealthTresholdVal, 1, 99);
	ImGui::Separator();

	ImGui::Checkbox("AimBot", &Config.AimBot);
	ImGui::Checkbox("SpinBot", &Config.SpinBot);
	ImGui::Checkbox("Neon WallHack", &Config.NeonWallHack);
	ImGui::Checkbox("DX ESP (boxes)", &Config.WallHackESP);
	ImGui::Checkbox("Recoil Control System", &Config.RecoilControlSystem);
	ImGui::Checkbox("Radar Hack", &Config.RadarHack);
	ImGui::Checkbox("TriggerBot", &Config.TriggerBot);
	ImGui::Checkbox("No Flash", &Config.NoFlash);
	ImGui::Checkbox("Bhop", &Config.Bhop);
	ImGui::Separator();
	ImGui::Checkbox("Health Treshold (AimBot)", &Config.HealthTreshold);
	ImGui::Separator();

	ImGui::ColorEdit4("Neon EntTeam WH Color", Config.ET_NEONESP);
	ImGui::ColorEdit4("Neon LocTeam WH Color", Config.LT_NEONESP);
	ImGui::ColorEdit4("DX ESP Color", Config.DX_ESP);
	ImGui::Separator();

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}