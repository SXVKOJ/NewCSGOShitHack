#include "includes.h"

void ToggleButton(const char* str_id, bool* v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
		*v = !*v;
	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255) : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
	else
		col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}

static int FOV = 90;
static bool AimBot = false;

void HACK::MenuThread()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");
	ImGui::SetWindowSize(ImVec2(522, 646), 0);

	ImGui::Separator();
	ImGui::SliderInt("FOV Slider", &FOV, 90, 160);
	ImGui::SliderInt("SpinBot Speed", &Config.SpinBotSpeed, 0, 200);
	ImGui::SliderInt("Trigger Bot Delay", &Config.TriggerBotDelay, 20, 200);
	ImGui::SliderInt("Bhop Delay", &Config.BhopDelay, 10, 30);
	ImGui::SliderInt("Default Delay", &Config.Delay, 1, 5);
	ImGui::SliderInt("Health Treshold value (Aimbot)", &Config.HealthTresholdVal, 1, 99);
	ImGui::Separator();

	ImGui::Checkbox("AimBot", &AimBot);
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

	//Config.FOV = FOV;
	//Config.AimBot = AimBot;
}