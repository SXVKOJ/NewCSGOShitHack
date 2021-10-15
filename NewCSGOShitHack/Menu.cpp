#include "includes.h"

int config::FOV = 90;
int config::SmoothStep = 1;
int config::SpinBotSpeed = 0;
int config::TargetBonePos = constVars.HeadBone;
int config::LegitAimBotDiff = 300;

bool config::console = false;
bool config::Bhop = false;
bool config::HealthTreshold = false;
bool config::TriggerBot = false;
bool config::NeonWallHack = false;
bool config::AimBot = false;
bool config::RecoilControlSystem = false;
bool config::RadarHack = false;
bool config::NoFlash = false;
bool config::WallHackESP = false;
bool config::SpinBot = false;
bool config::SmoothAimBot = false;
bool config::ThirdPersonView = false;
bool config::TPSActive = false;
bool config::AimLegitMode = false;
bool config::AimingAssistance = false;
bool config::TriggerBotInAimBot = false;

bool config::ImGui_Init = false;
bool config::ImGui_Attached = false;

int config::esp::BoxWidth = 3;
int config::esp::LineWidth = 1;

int config::HealthTresholdVal = 33;
int config::BhopDelay = 17;
int config::TriggerBotCooldown = 65;
int config::MainThreadDelay = 1;

int config::AimBotHotKey = 18;   // VK_ALT
int config::EndHotKey = 0x23;   // VK_END
int config::MenuHotKey = 0x24; // VK_HOME
bool config::MenuActive = false;

float config::esp::LT_NEONESP[3] = { 0, 1, 1 };
float config::esp::ET_NEONESP[3] = { 1, 0, 1 };
float config::esp::DX_ESP[3] = { 1, 0, 1 };

bool config::esp::HP = false;	
bool config::esp::ESPBones = false;
bool config::esp::Lines = true;

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
static bool BonesIds = false;

void HACK::LoadImageToDll(BYTE* Image, LPDIRECT3DDEVICE9& pDevice)
{
	D3DXCreateTextureFromFileInMemoryEx(pDevice, &NameArry, sizeof(NameArry), 495, 659, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tImage);
}

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
		ImGui::SliderInt("Bhop Cooldown", &config::BhopDelay, 10, 30);
		ImGui::SliderInt("Default Cooldown (for FPS)", &config::MainThreadDelay, 1, 100);
		ImGui::Separator();
		ImGui::Checkbox("AimBot", &config::AimBot);
		ImGui::Separator();
		ImGui::Checkbox("SpinBot", &config::SpinBot);
		ImGui::Separator();
		ImGui::Checkbox("Glow ESP (Neon)", &config::NeonWallHack);
		ImGui::Separator();
		ImGui::Checkbox("DX ESP (boxes)", &config::WallHackESP);
		ImGui::Separator();
		ImGui::Checkbox("Recoil Control System", &config::RecoilControlSystem);
		ImGui::Separator();
		ImGui::Checkbox("Radar Hack", &config::RadarHack);
		ImGui::Separator();
		ImGui::Checkbox("TriggerBot", &config::TriggerBot);
		if (config::TriggerBot)
			ImGui::Checkbox("Inside AimBot?", &config::TriggerBotInAimBot);

		ImGui::Separator();
		ImGui::Checkbox("No Flash", &config::NoFlash);
		ImGui::Separator();
		ImGui::Checkbox("Bhop", &config::Bhop);
		ImGui::Separator();
	}
	
	else if (CurrTab == 1)
	{
		// VIEW
		ImGui::Separator();
		ImGui::SliderInt("FOV Slider", &config::FOV, 90, 170);
		ImGui::Separator();
		ImGui::Checkbox("Third Person Mode", &config::ThirdPersonView);
	}	

	else if (CurrTab == 2)
	{
		// AIMBOT
		ImGui::Separator();
		ImGui::SliderInt("SpinBot Speed", &config::SpinBotSpeed, 0, 200);
		ImGui::SliderInt("Trigger Bot Cooldown", &config::TriggerBotCooldown, 20, 5000);
		ImGui::SliderInt("Health Treshold value", &config::HealthTresholdVal, 1, 99);
		ImGui::Separator();
		ImGui::Checkbox("Health Treshold", &config::HealthTreshold);
		ImGui::Separator();
		ImGui::Checkbox("Smooth Mode", &config::SmoothAimBot);
		if (config::SmoothAimBot)
			ImGui::SliderInt("Smooth", &config::SmoothStep, 1, 10);

		ImGui::Separator();
		ImGui::Checkbox("Legit Mode", &config::AimLegitMode);
		ImGui::Separator();
		ImGui::Checkbox("Aiming assistance", &config::AimingAssistance);

		if (config::AimingAssistance)
			ImGui::SliderInt("Min Distanse", &config::LegitAimBotDiff, 1, 1920);
		
		ImGui::Separator();
		ImGui::InputInt("Target Bone", &config::TargetBonePos, 1, 79, 0);
		ImGui::Checkbox("Bones id's", &BonesIds);
		if ((tImage != nullptr) && BonesIds)
			ImGui::Image(tImage, ImVec2(495, 659));
	}	

	else if (CurrTab == 3)
	{
		// WALLHACK
		ImGui::Separator();
		ImGui::ColorEdit4("EntTeam Color", config::esp::ET_NEONESP);
		ImGui::ColorEdit4("LocTeam Color", config::esp::LT_NEONESP);
		ImGui::ColorEdit4("ESP Color", config::esp::DX_ESP);
		ImGui::Separator();
		ImGui::Checkbox("Draw Bones", &config::esp::ESPBones);
		ImGui::Checkbox("Draw Health", &config::esp::HP);
		ImGui::Separator();
		ImGui::InputInt("Box Width", &config::esp::BoxWidth, 1, 10, 0);
		ImGui::InputInt("Line Width", &config::esp::LineWidth, 1, 10, 0);
	}

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}