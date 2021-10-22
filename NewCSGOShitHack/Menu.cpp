#include "includes.h"

int config::FOV = 90;
int config::SmoothStep = 1;
int config::SpinBotSpeed = 0;
int config::TargetBonePos = constVars.HeadBone;
int config::LegitAimBotDiff = 300;
bool config::FPSMode = false;

bool config::console = false;
bool config::Bhop = false;
bool config::HealthTreshold = false;
bool config::TriggerBot = false;
bool config::NeonWallHack = false;
bool config::AimBot = false;
bool config::RecoilControlSystem = false;
bool config::RadarHack = false;
bool config::NoFlash = true;
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

int config::SkinChanger::CurrentSkinID = 0;
int config::SkinChanger::CurrentWeaponID = 0;
int config::SkinChanger::StatTrackVal = 1337;
int config::SkinChanger::KnifeType = 0;
bool config::SkinChanger::StatTrack = false;
bool config::SkinChanger::CustomName = false;
char* config::SkinChanger::szCustomName = nullptr;
float config::SkinChanger::wear = 0.000001f;

bool config::Aim::Compensation = false;
int config::Aim::CompensationVal = 0;
int config::Aim::CurrentWeaponID = 0;

float config::View::offset_x = 0;
float config::View::offset_y = 0;
float config::View::offset_z = 0;
bool config::View::custom = false;

int config::HealthTresholdVal = 33;
int config::BhopDelay = 17;
int config::TriggerBotCooldown = 17;
int config::MainThreadDelay = 1;

int config::HotKeys::AimBot = 18;   // VK_ALT
int config::HotKeys::End = VK_END;   // VK_END
int config::HotKeys::Menu = VK_HOME; // VK_INSERT
bool config::MenuActive = false;

float config::esp::LT_NEONESP[3] = { 0, 1, 1 };
float config::esp::ET_NEONESP[3] = { 1, 0, 1 };
float config::esp::DX_ESP[3] = { 1, 0, 1 };
float config::esp::health::color[3] = { 1, 0, 1 };
float config::esp::weapon::color[3] = { 0, 1, 1 };

int config::esp::health::offset_x = 0;
int config::esp::health::offset_y = 0;
int config::esp::weapon::offset_x = 20;
int config::esp::weapon::offset_y = 0;
int config::esp::health::BarsPos = 0; // 0 - top, 1 - left, 2 - bottom, 3 - right

bool config::esp::health::HealthBar = false;
bool config::esp::health::ArmorBar = false;
bool config::esp::weapon::ShowWeapon = false;
bool config::esp::HP = false;
bool config::esp::ESPBones = false;
bool config::esp::Lines = true;
bool config::esp::health::custom_color = false;
bool config::esp::weapon::custom_color = false;

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
static bool _SkinChanger = false;

void HACK::LoadImageToDll(BYTE* Image, LPDIRECT3DDEVICE9& pDevice)
{
	D3DXCreateTextureFromFileInMemoryEx(pDevice, Image, sizeof(Image), 495, 659, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tImage);
}

void HACK::MenuThread()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");
	ImGui::SetWindowSize(ImVec2(700, 650));
    
	{ /*                 Tabs                  */
		if (ImGui::Button("Main", ImVec2(150, 30)))
			CurrTab = 0;

		ImGui::SameLine();
		if (ImGui::Button("Visuals", ImVec2(150, 30)))
			CurrTab = 1;

		ImGui::SameLine();
		if (ImGui::Button("Aimbot", ImVec2(150, 30)))
			CurrTab = 2;

		ImGui::SameLine();
		if (ImGui::Button("SkinChanger", ImVec2(150, 30)))
			CurrTab = 3;
	}
	
	if (true)
	{
		if (CurrTab == 0) 
		{ /*     Main   */
			using namespace config;

			ImGui::Separator();

			ImGui::Text("Main Functions");
			ImGui::Separator();

			if (ImGui::RadioButton("Bhop", Bhop))
				Bhop = !Bhop;
			if (ImGui::RadioButton("AimBot", AimBot))
				AimBot = !AimBot;
			if (ImGui::RadioButton("Glow ESP", NeonWallHack))
				NeonWallHack = !NeonWallHack;
			if (ImGui::RadioButton("Default ESP", WallHackESP))
				WallHackESP = !WallHackESP;
			if (ImGui::RadioButton("Recoil Control System", RecoilControlSystem))
				RecoilControlSystem = !RecoilControlSystem;
			if (ImGui::RadioButton("Radar Hack", RadarHack))
				RadarHack = !RadarHack;
			if (ImGui::RadioButton("Trigger Bot", config::TriggerBot))
				TriggerBot = !TriggerBot;

			ImGui::Text("_Settings_");
			ImGui::Separator();

			if (ImGui::RadioButton("FPS mode", config::FPSMode))
				config::FPSMode = !config::FPSMode;
		}
		else if (CurrTab == 1) 
		{ /*      Visuals    */
			using namespace config::esp;

			ImGui::Text("View");
			ImGui::Separator();
			ImGui::SliderInt("FOV Slider", &config::FOV, 90, 170);
			ImGui::SameLine();
			if (ImGui::Button("Reset", ImVec2(100, 25)))
			{
				config::FOV = 90;
			}

			if (ImGui::RadioButton("Third Person Mode", config::ThirdPersonView))
				config::ThirdPersonView = !config::ThirdPersonView;
			
			// TODO: the ability to shift the position of the weapon
			if (ImGui::RadioButton("Custow View Offset", config::View::custom))
				config::View::custom = !config::View::custom;

			if (config::View::custom)
			{
				ImGui::SliderFloat("offset_x", &config::View::offset_x, -35, 35);
				ImGui::SliderFloat("offset_y", &config::View::offset_y, -35, 35);
				ImGui::SliderFloat("offset_z", &config::View::offset_z, -35, 35);
				ImGui::SameLine();
				if (ImGui::Button("_Reset_", ImVec2(100, 25)))
				{
					config::View::offset_x = 0;
					config::View::offset_y = 0;
					config::View::offset_z = 0;
				}
			}
			
			/*                         ESP SHIT                              */
			ImGui::Text("ESP");
			ImGui::Separator();

			if (ImGui::RadioButton("Show Boxes", config::WallHackESP))
				config::WallHackESP = !config::WallHackESP;
			if (ImGui::RadioButton("Show Lines", Lines))
				Lines = !Lines;
			if (ImGui::RadioButton("Show Health", HP))
				HP = !HP;
			if (ImGui::RadioButton("Show Bones", ESPBones))
				ESPBones = !ESPBones;
			if (ImGui::RadioButton("Show Weapon", weapon::ShowWeapon))
				weapon::ShowWeapon = !weapon::ShowWeapon;
			if (ImGui::RadioButton("Show HealthBar", health::HealthBar))
				health::HealthBar = !health::HealthBar;
			if (ImGui::RadioButton("Show ArmorBar", health::ArmorBar))
				health::ArmorBar = !health::ArmorBar;

			if (health::HealthBar || health::ArmorBar)
			{
				ImGui::SameLine();
				ImGui::InputInt("HB Pos", &health::BarsPos, 1, 1);
			}

			ImGui::Text("Colors");
			ImGui::Separator();

			ImGui::ColorEdit4("Boxes", config::esp::DX_ESP);
			ImGui::ColorEdit4("Weapon", config::esp::weapon::color);
			ImGui::ColorEdit4("Health", config::esp::health::color);
			ImGui::ColorEdit4("Glow (ET)", config::esp::ET_NEONESP);
			ImGui::ColorEdit4("Glow (LT)", config::esp::LT_NEONESP);

			ImGui::Text("Offsets");
			ImGui::Separator();

			ImGui::SliderInt("Health x", &config::esp::health::offset_x, -150, 150);
			ImGui::SliderInt("Health y", &config::esp::health::offset_y, -150, 150);
			ImGui::SliderInt("Weapon x", &config::esp::weapon::offset_x, -150, 150);
			ImGui::SliderInt("Weapon y", &config::esp::weapon::offset_y, -150, 150);
		}
		else if (CurrTab == 2)
		{ /*     AimBot     */
			using namespace config;

			ImGui::Text("AimBot");
			ImGui::Separator();

			if (ImGui::RadioButton("SpinBot", SpinBot))
				SpinBot = !SpinBot;

			if (SpinBot)
			{
				ImGui::SameLine();
				ImGui::SliderInt("Speed", &SpinBotSpeed, 0, 220);
			}

			if (ImGui::RadioButton("TriggerBot", TriggerBot))
				TriggerBot = !TriggerBot;

			if (TriggerBot)
			{
				ImGui::SameLine();
				ImGui::SliderInt("cooldown", &TriggerBotCooldown, 20, 1000);
			}

			if (ImGui::RadioButton("Health Treshold", HealthTreshold))
				HealthTreshold = !HealthTreshold;

			if (HealthTreshold)
			{
				ImGui::SameLine();
				ImGui::SliderInt("Val", &config::HealthTresholdVal, 1, 100);
			}

			ImGui::InputInt("Target Bone", &config::TargetBonePos, 1, 79, 0);
			// Compensation
			ImGui::Text("Compensation");
			ImGui::Separator();

			if (ImGui::RadioButton("Compensation", Aim::Compensation))
			{
				Aim::Compensation = !Aim::Compensation;
			}

			if (Aim::Compensation)
			{
				ImGui::Text("Current Weapon Name: ");
				ImGui::SameLine();
				ImGui::Text(Game.GetWeaponName(config::Aim::CurrentWeaponID).c_str());

				ImGui::InputInt("_Weapon ID", &config::Aim::CurrentWeaponID, 1, 30);
				ImGui::SameLine();
				if (ImGui::Button("_Curr_", ImVec2(100, 25)))
				{
					config::Aim::CurrentWeaponID = Game.GetCurrentWeapon();
				}
				ImGui::InputInt("CompVal   ", &config::Aim::CompensationVal, 1, 30);
				ImGui::SameLine();
				if (ImGui::Button("_Save_", ImVec2(100, 25)))
				{
					USER_COMP_CFG[config::Aim::CurrentWeaponID] = config::Aim::CompensationVal;
				}
			}

			ImGui::Text("Legit");
			ImGui::Separator();

			if (ImGui::RadioButton("Smooth Mode", SmoothAimBot))
				SmoothAimBot = !SmoothAimBot;

			if (SmoothAimBot)
			{
				ImGui::SameLine();
				ImGui::SliderInt("val", &config::SmoothStep, 1, 180);
			}

			if (ImGui::RadioButton("through walls", AimLegitMode))
				AimLegitMode = !AimLegitMode;

			if (ImGui::RadioButton("Aiming assistance", AimingAssistance))
				AimingAssistance = !AimingAssistance;

			if (AimingAssistance)
			{
				ImGui::SameLine();
				ImGui::SliderInt("Treshold", &config::LegitAimBotDiff, 1, 900);
			}
		}
		else if (CurrTab == 3) 
		{   /*    SkinChanger   */
			ImGui::Text("SkinChanger");
			ImGui::Separator();

			if (ImGui::RadioButton("_SkinChanger_", _SkinChanger))
			{
				_SkinChanger = !_SkinChanger;
			}

			if (_SkinChanger)
			{
				ImGui::SliderInt("Knife Type", &config::SkinChanger::KnifeType, 0, 10);
				ImGui::SameLine();
				ImGui::Text(KnifeTypeToName().c_str());
				ImGui::Separator();

				ImGui::Text("Current Weapon Name: ");
				ImGui::SameLine();
				ImGui::Text(Game.GetWeaponName(config::SkinChanger::CurrentWeaponID).c_str());

				if (ImGui::RadioButton("StatTrack", config::SkinChanger::StatTrack))
					config::SkinChanger::StatTrack = !config::SkinChanger::StatTrack;

				if (config::SkinChanger::StatTrack)
				{
					ImGui::SameLine();
					ImGui::InputInt("st val", &config::SkinChanger::StatTrackVal, 1, 20);
				}			
				if (ImGui::RadioButton("Custom Weapon Name", config::SkinChanger::CustomName))
					config::SkinChanger::CustomName = !config::SkinChanger::CustomName;

				if (config::SkinChanger::CustomName)
					ImGui::InputText("wName", config::SkinChanger::szCustomName, sizeof(config::SkinChanger::szCustomName));
			
				ImGui::SliderFloat("skin wear", &config::SkinChanger::wear, 0.f, 1.f);
				ImGui::InputInt("Weapon ID", &config::SkinChanger::CurrentWeaponID, 1, 30);
				ImGui::SameLine();
				if (ImGui::Button("Current", ImVec2(100, 25)))
				{
					config::SkinChanger::CurrentWeaponID = Game.GetCurrentWeapon();
				}
				ImGui::InputInt("Skin   ID", &config::SkinChanger::CurrentSkinID, 1, 30);
				ImGui::SameLine();
				if (ImGui::Button("_Save_", ImVec2(100, 25)))
				{
					UserCFG[config::SkinChanger::CurrentWeaponID] = config::SkinChanger::CurrentSkinID;
					Hack.FullForceUpdate();
				}

				ImGui::TextColored(ImVec4(1, 1, 0, 1), "Current Config");
				ImGui::BeginChild("Scrolling");
				for (int i = 0; i < 526; i++)
				{
					if (UserCFG[i] != 0)
					{
						ImGui::Text(Game.GetWeaponName(i).c_str());
						ImGui::SameLine();
						ImGui::Text(std::to_string(UserCFG[i]).c_str());
					}
				}
				ImGui::EndChild();
			}
		}
	}

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}