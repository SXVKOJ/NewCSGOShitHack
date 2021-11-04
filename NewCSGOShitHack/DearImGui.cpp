#include "includes.h"

static int CurrTab = 0;

VOID DearImGui::Init()
{
	ImGui::CreateContext();

	D3DDEVICE_CREATION_PARAMETERS CP;
	pDevice->GetCreationParameters(&CP);
	mDevice.Window = mDevice.GetProcessWindow();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontDefault();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui_ImplWin32_Init(mDevice.Window);
	ImGui_ImplDX9_Init(pDevice);
}

VOID DearImGui::SetCustomStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowBorderSize = 0.0f;
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void DearImGui::Draw()
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
			using namespace config::hack;

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
			if (ImGui::RadioButton("Trigger Bot", TriggerBot))
				TriggerBot = !TriggerBot;
		}
		else if (CurrTab == 1) 
		{ /*      Visuals    */
			using namespace config;

			ImGui::Text("View");
			ImGui::Separator();
			ImGui::SliderInt("FOV Slider", &hack::FOV, 90, 170);
			ImGui::SameLine();
			if (ImGui::Button("Reset", ImVec2(100, 25)))	
				hack::FOV = 90;

			if (ImGui::RadioButton("Third Person Mode", config::hack::ThirdPersonView))
				config::hack::ThirdPersonView = !config::hack::ThirdPersonView;
			
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

			if (ImGui::RadioButton("Show Boxes", config::hack::WallHackESP))
				config::hack::WallHackESP = !config::hack::WallHackESP;
			if (ImGui::RadioButton("Show Lines", esp::Lines))
				esp::Lines = !esp::Lines;
			if (ImGui::RadioButton("Show Health", esp::HealthBar))
				esp::HealthBar = !esp::HealthBar;
			if (ImGui::RadioButton("Show Weapon", esp::ShowWeapon))
				esp::ShowWeapon = !esp::ShowWeapon;
			if (ImGui::RadioButton("Show HealthBar", esp::HealthBar))
				esp::HealthBar = !esp::HealthBar;
			if (ImGui::RadioButton("Show ArmorBar", esp::ArmorBar))
				esp::ArmorBar = !esp::ArmorBar;

			if (esp::HealthBar || esp::ArmorBar)
			{
				ImGui::SameLine();
				ImGui::InputInt("bar Pos", &esp::bar::BarsPos, 1, 1);
			}

			ImGui::Text("Colors");
			ImGui::Separator();

			ImGui::ColorEdit4("Boxes", esp::colors::ET_ESP);
			ImGui::ColorEdit4("Weapon", esp::weapon::color);
			ImGui::ColorEdit4("Health", esp::colors::HealthColor);
			ImGui::ColorEdit4("Glow (ET)", esp::colors::ET_GLOW);
			ImGui::ColorEdit4("Glow (LT)", esp::colors::LT_GLOW);

			ImGui::Text("Offsets");
			ImGui::Separator();

			ImGui::SliderInt("Health x", &config::esp::bar::offset_x, -150, 150);
			ImGui::SliderInt("Health y", &config::esp::bar::offset_y, -150, 150);
			ImGui::SliderInt("Weapon x", &config::esp::weapon::offset_x, -150, 150);
			ImGui::SliderInt("Weapon y", &config::esp::weapon::offset_y, -150, 150);
		}
		else if (CurrTab == 2)
		{ /*     AimBot     */
			using namespace config;

			ImGui::Text("AimBot");
			ImGui::Separator();

			if (ImGui::RadioButton("SpinBot", hack::SpinBot))
				hack::SpinBot = !hack::SpinBot;

			if (hack::SpinBot)
			{
				ImGui::SameLine();
				ImGui::SliderInt("Speed", &aimbot::SpinBotSpeed, 0, 220);
			}

			if (ImGui::RadioButton("TriggerBot", hack::TriggerBot))
				hack::TriggerBot = !hack::TriggerBot;

			if (hack::TriggerBot)
			{
				ImGui::SameLine();
				ImGui::SliderInt("cooldown", &aimbot::TriggerBotCooldown, 20, 1000);
			}

			ImGui::SliderInt("Sniper weapon triggerbot cooldown", &config::aimbot::SniperWeaponTriggerBotCooldown, 10, 250);

			ImGui::InputInt("Target Bone", &config::aimbot::TargetBonePos, 1, 79, 0);

			ImGui::Text("Legit");
			ImGui::Separator();

			if (ImGui::RadioButton("Smooth Mode", hack::SmoothAimBot))
				hack::SmoothAimBot = !hack::SmoothAimBot;

			if (hack::SmoothAimBot)
			{
				ImGui::SameLine();
				ImGui::SliderInt("val", &config::aimbot::SmoothVal, 1, 180);
			}

			if (ImGui::RadioButton("Through walls", aimbot::LegitMode))
				aimbot::LegitMode = !aimbot::LegitMode;

			if (ImGui::RadioButton("Aiming assistance", hack::AimingAssistance))
				hack::AimingAssistance = !hack::AimingAssistance;

			if (hack::AimingAssistance)
			{
				ImGui::SameLine();
				ImGui::SliderInt("Treshold", &config::aimbot::LegitDiff, 1, 900);
			}
		}
		else if (CurrTab == 3) 
		{   /*    SkinChanger   */
			using namespace config;

			ImGui::Text("SkinChanger");
			ImGui::Separator();

			if (ImGui::RadioButton("*SkinChanger", hack::SkinChanger))
			{
				hack::SkinChanger = !hack::SkinChanger;
			}

			if (hack::SkinChanger)
			{
				ImGui::Text("Current Weapon Name: ");
				ImGui::SameLine();
				ImGui::Text(Engine.GetWeaponName(config::SkinChanger::CurrentWeaponID).c_str());

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
					config::SkinChanger::CurrentWeaponID = lPlayer.GetCurrentWeapon();
				}
				ImGui::InputInt("Skin   ID", &config::SkinChanger::CurrentSkinID, 1, 30);
				ImGui::SameLine();
				if (ImGui::Button("_Save_", ImVec2(100, 25)))
				{
					Engine.SkinChangerCFG[config::SkinChanger::CurrentWeaponID] = config::SkinChanger::CurrentSkinID;
					Hack.FullForceUpdate();
				}

				ImGui::TextColored(ImVec4(1, 1, 0, 1), "Current Config");
				ImGui::BeginChild("Scrolling");
				for (int i = 0; i < 70; i++)
				{
					if (Engine.SkinChangerCFG[i] != 0)
					{
						ImGui::Text(Engine.GetWeaponName(i).c_str());
						ImGui::SameLine();
						ImGui::Text(std::to_string(Engine.SkinChangerCFG[i]).c_str());
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