#include "includes.h"

void HACK::MenuThread()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Settings");

	ImGui::Separator();
	ImGui::SliderInt("FOV Slider", &Config.FOV, 90, 160);
	ImGui::Separator();

	ImGui::Checkbox("AimBot", &Config.AimBot);
	ImGui::Separator();

	ImGui::ColorEdit4("Neon EntTeam WH Color", Config.ET_NEONESP);
	ImGui::ColorEdit4("Neon LocTeam WH Color", Config.LT_NEONESP);
	ImGui::ColorEdit4("DX ESP Color", Config.DX_ESP);

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}