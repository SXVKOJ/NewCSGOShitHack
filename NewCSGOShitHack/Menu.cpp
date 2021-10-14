#include "includes.h"

int FOV = 90;
int SmoothStep = 1;
int SpinBotSpeed = 0;
int TargetBonePos = constVars.HeadBone;
int LegitAimBotDiff = 300;

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
bool AimLegitMode = false;
bool AimingAssistance = false;
bool TriggerBotInAimBot = false;

bool ImGui_Init = false;
bool ImGui_Attached = false;

int BoxWidth = 3;
int LineWidth = 1;

int HealthTresholdVal = 33;
int BhopDelay = 17;
int TriggerBotCooldown = 65;
int MainThreadDelay = 1;

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

	ImGui::InvisibleButton(str_id, ImVec2(width, height));
	if (ImGui::IsItemClicked())
		*v = !*v;

	float t = *v ? 1.0f : 0.0f;

	ImGuiContext& g = *GImGui;
	float ANIM_SPEED = 0.08f;
	if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *v ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
	else
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
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
		ImGui::SliderInt("Bhop Cooldown", &BhopDelay, 10, 30);
		ImGui::SliderInt("Default Cooldown (for FPS)", &MainThreadDelay, 1, 10);
		ImGui::Separator();
		ImGui::Checkbox("AimBot", &AimBot);
		ImGui::Separator();
		ImGui::Checkbox("SpinBot", &SpinBot);
		ImGui::Separator();
		ImGui::Checkbox("Glow ESP (Neon)", &NeonWallHack);
		ImGui::Separator();
		ImGui::Checkbox("DX ESP (boxes)", &WallHackESP);
		ImGui::Separator();
		ImGui::Checkbox("Recoil Control System", &RecoilControlSystem);
		ImGui::Separator();
		ImGui::Checkbox("Radar Hack", &RadarHack);
		ImGui::Separator();
		ImGui::Checkbox("TriggerBot", &TriggerBot);
		if (TriggerBot)
			ImGui::Checkbox("Inside AimBot?", &TriggerBotInAimBot);

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
		ImGui::SliderInt("FOV Slider", &FOV, 90, 200);
		ImGui::Separator();
		ImGui::Checkbox("Third Person Mode", &ThirdPersonView);
	}	

	else if (CurrTab == 2)
	{
		// AIMBOT
		ImGui::Separator();
		ImGui::SliderInt("SpinBot Speed", &SpinBotSpeed, 0, 200);
		ImGui::SliderInt("Trigger Bot Cooldown", &TriggerBotCooldown, 20, 5000);
		ImGui::SliderInt("Health Treshold value", &HealthTresholdVal, 1, 99);
		ImGui::Separator();
		ImGui::Checkbox("Health Treshold", &HealthTreshold);
		ImGui::Separator();
		ImGui::Checkbox("Smooth Mode", &SmoothAimBot);
		if (SmoothAimBot)
			ImGui::SliderInt("Smooth", &SmoothStep, 1, 10);

		ImGui::Separator();
		ImGui::Checkbox("Legit Mode", &AimLegitMode);
		ImGui::Separator();
		ImGui::Checkbox("Aiming assistance", &AimingAssistance);

		if (AimingAssistance)
			ImGui::SliderInt("Min Distanse", &LegitAimBotDiff, 1, 3000);
		
		ImGui::Separator();
		ImGui::InputInt("Target Bone", &TargetBonePos, 1, 100, 0);
	}	

	else if (CurrTab == 3)
	{
		// WALLHACK
		ImGui::Separator();
		ImGui::ColorEdit4("EntTeam Color", ET_NEONESP);
		ImGui::ColorEdit4("LocTeam Color", LT_NEONESP);
		ImGui::ColorEdit4("ESP Color", DX_ESP);
		ImGui::Separator();
		ImGui::InputInt("Box Width", &BoxWidth, 1, 50, 0);
		ImGui::InputInt("Line Width", &LineWidth, 1, 50, 0);
	}

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}