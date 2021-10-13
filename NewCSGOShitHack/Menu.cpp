#include "includes.h"

int FOV = 90;
int SpinBotSpeed = 0;
int TargetBonePos = constVars.HeadBone;

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
bool SmoothAimBot = false;
bool SilentAimBot = false;
bool ThirdPersonView = false;
bool TPSActive = false;

bool ImGui_Init = false;
bool ImGui_Attached = false;

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

static int CurrTab = 0;

void HACK::MenuThread()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");
	ImGui::SetWindowSize(ImVec2(666, 680), 0);

	if (ImGui::Button("Main", ImVec2(150, 30)))
		CurrTab = 0;

	ImGui::SameLine();
	if (ImGui::Button("View", ImVec2(150, 30)))
		CurrTab = 1;

	ImGui::SameLine();
	if (ImGui::Button("Aimbot", ImVec2(150, 30)))
		CurrTab = 2;

	ImGui::SameLine();
	if (ImGui::Button("WallHack", ImVec2(150, 30)))
		CurrTab = 3;

	if (CurrTab == 0)
	{
		// MAIN THREAD
		ImGui::Separator();
		ImGui::SliderInt("Bhop Delay", &BhopDelay, 10, 30);
		ImGui::SliderInt("Default Delay", &Delay, 1, 5);
		ImGui::Separator();
		ImGui::Checkbox("AimBot", &AimBot);
		ImGui::Separator();
		ImGui::Checkbox("Smooth AimBot", &SmoothAimBot);
		ImGui::Separator();
		ImGui::Checkbox("SpinBot", &SpinBot);
		ImGui::Separator();
		ImGui::Checkbox("Neon WallHack", &NeonWallHack);
		ImGui::Separator();
		ImGui::Checkbox("DX ESP (boxes)", &WallHackESP);
		ImGui::Separator();
		ImGui::Checkbox("Recoil Control System", &RecoilControlSystem);
		ImGui::Separator();
		ImGui::Checkbox("Radar Hack", &RadarHack);
		ImGui::Separator();
		ImGui::Checkbox("TriggerBot", &TriggerBot);
		ImGui::Separator();
		ImGui::Checkbox("No Flash", &NoFlash);
		ImGui::Separator();
		ImGui::Checkbox("Bhop", &Bhop);
		ImGui::Separator();
	}
	
	else if (CurrTab == 1)
	{
		// VIEW
		ImGui::Separator();
		ImGui::SliderInt("FOV Slider", &FOV, 90, 160);
		ImGui::Separator();
		ImGui::Checkbox("Third Person Mode", &ThirdPersonView);
	}	

	else if (CurrTab == 2)
	{
		// AIMBOT
		ImGui::Separator();
		ImGui::SliderInt("SpinBot Speed", &SpinBotSpeed, 0, 200);
		ImGui::SliderInt("Trigger Bot Delay", &TriggerBotDelay, 20, 5000);
		ImGui::SliderInt("Health Treshold value (Aimbot)", &HealthTresholdVal, 1, 99);
		ImGui::Separator();
		ImGui::Checkbox("Health Treshold (AimBot)", &HealthTreshold);
		ImGui::Checkbox("Smooth Mode (+Legit)", &SmoothAimBot);
		ImGui::Separator();
		ImGui::InputInt("Target Bone", &TargetBonePos, 1, 100, 0);
	}	

	else if (CurrTab == 3)
	{
		// WALLHACK
		ImGui::Separator();
		ImGui::ColorEdit4("Neon EntTeam WH Color", ET_NEONESP);
		ImGui::ColorEdit4("Neon LocTeam WH Color", LT_NEONESP);
		ImGui::ColorEdit4("DX ESP Color", DX_ESP);
		ImGui::Separator();
	}

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}