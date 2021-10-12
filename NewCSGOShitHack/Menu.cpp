#include "includes.h"

int FOV = 90;
int SpinBotSpeed = 0;

bool Bhop = false;
bool HealthTreshold = false;
bool TriggerBot = false;
bool NeonWallHack = false;
bool AimBot = false;
bool RecoilControlSystem = false;
bool RadarHack = false;
bool NoFlash = false;
bool WallHackESP = false;
bool SpinBot = false;
bool SilentAim = false;

int HealthTresholdVal = 33;
int BhopDelay = 17;
int TriggerBotDelay = 65;
int Delay = 1;

int AimBotHotKey = 18;   // VK_ALT
int EndHotKey = 0x23;   // VK_END
int MenuHotKey = 0x24; // VK_HOME

float LT_NEONESP[3] = { 0, 1, 1 };
float ET_NEONESP[3] = { 1, 0, 1 };
float DX_ESP[3] = { 1, 0, 1 };

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

void HACK::MenuThread()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");
	ImGui::SetWindowSize(ImVec2(522, 646), 0);

	ImGui::Separator();
	ImGui::SliderInt("FOV Slider", &FOV, 90, 160);
	ImGui::SliderInt("SpinBot Speed", &SpinBotSpeed, 0, 200);
	ImGui::SliderInt("Trigger Bot Delay", &TriggerBotDelay, 20, 200);
	ImGui::SliderInt("Bhop Delay", &BhopDelay, 10, 30);
	ImGui::SliderInt("Default Delay", &Delay, 1, 5);
	ImGui::SliderInt("Health Treshold value (Aimbot)", &HealthTresholdVal, 1, 99);
	ImGui::Separator();

	ImGui::Checkbox("AimBot", &AimBot);
	ImGui::Checkbox("Silent AimBot", &SilentAim);
	ImGui::Checkbox("SpinBot", &SpinBot);
	ImGui::Checkbox("Neon WallHack", &NeonWallHack);
	ImGui::Checkbox("DX ESP (boxes)", &WallHackESP);
	ImGui::Checkbox("Recoil Control System", &RecoilControlSystem);
	ImGui::Checkbox("Radar Hack", &RadarHack);
	ImGui::Checkbox("TriggerBot", &TriggerBot);
	ImGui::Checkbox("No Flash", &NoFlash);
	ImGui::Checkbox("Bhop", &Bhop);
	ImGui::Separator();
	ImGui::Checkbox("Health Treshold (AimBot)", &HealthTreshold);
	ImGui::Separator();

	ImGui::ColorEdit4("Neon EntTeam WH Color", ET_NEONESP);
	ImGui::ColorEdit4("Neon LocTeam WH Color", LT_NEONESP);
	ImGui::ColorEdit4("DX ESP Color", DX_ESP);
	ImGui::Separator();

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}