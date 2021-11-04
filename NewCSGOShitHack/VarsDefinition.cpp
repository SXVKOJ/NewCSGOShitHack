#include "includes.h"

// cVars
int cVars::Flags::OnGround = 257;
int cVars::Flags::Active	  = 5;
int cVars::Flags::InActive = 4;
int cVars::Flags::ON       = 1;
int cVars::Flags::OFF      = 0;

int cVars::WallHack::posTop    = 0;
int cVars::WallHack::posLeft   = 1;
int cVars::WallHack::posBottom = 2;
int cVars::WallHack::posRight  = 3;

int cVars::PlayerStructSize = 0x10;
int cVars::HeadBone = 8;
// menu
int  config::hack::FOV = 90;
bool config::hack::Bhop = TRUE;
bool config::hack::TriggerBot = FALSE;
bool config::hack::NeonWallHack = TRUE;
bool config::hack::AimBot = FALSE;
bool config::hack::RecoilControlSystem = FALSE;
bool config::hack::RadarHack = TRUE;
bool config::hack::NoFlash = TRUE;
bool config::hack::WallHackESP = FALSE;
bool config::hack::SpinBot = FALSE;
bool config::hack::AimingAssistance = FALSE;
bool config::hack::SmoothAimBot = FALSE;
bool config::hack::ThirdPersonView = FALSE;
bool config::hack::TPSActive = FALSE;
bool config::hack::TriggerBotInAimBot = FALSE;
bool config::hack::SkinChanger = FALSE;
// aimbot
int		config::aimbot::TriggerBotCooldown = 1;
int		config::aimbot::SmoothVal = 10;
int		config::aimbot::SpinBotSpeed = 0;
int		config::aimbot::TargetBonePos = cVars::HeadBone;
int		config::aimbot::LegitDiff = 0;
int		config::aimbot::CompensationVal = 0;
int		config::aimbot::SniperWeaponTriggerBotCooldown = 30;
bool	config::aimbot::Compensation = FALSE;
bool	config::aimbot::LegitMode = TRUE;
// view
float	config::View::offset_x = 0;
float	config::View::offset_y = 0;
float	config::View::offset_z = 0;
bool	config::View::custom = FALSE;
// Skin Changer
int		config::SkinChanger::CurrentSkinID = 0;
int		config::SkinChanger::CurrentWeaponID = 0;
int		config::SkinChanger::StatTrackVal = 1337;
bool	config::SkinChanger::CustomName = FALSE;
bool	config::SkinChanger::StatTrack = TRUE;
char*	config::SkinChanger::szCustomName = 0;
int		config::SkinChanger::KnifeType = 0;
float	config::SkinChanger::wear = 0.000001;
// HotKeys
int config::HotKeys::AimBot = 18;
int config::HotKeys::End = VK_END;
int config::HotKeys::Menu = VK_HOME;

int config::esp::box::Width = 3;
int config::esp::line::Width = 1;

float config::esp::colors::LT_GLOW[3] = { 0, 1, 1 };
float config::esp::colors::ET_GLOW[3] = { 1, 0, 1 };
float config::esp::colors::ET_ESP[3] = { 0, 1, 1 };
float config::esp::colors::HealthColor[3] = { 1, 0, 1 };

bool config::esp::HealthBar = TRUE;
bool config::esp::ArmorBar = TRUE;
bool config::esp::Boxes = TRUE;
bool config::esp::Lines = TRUE;
bool config::esp::ShowNames = FALSE;
bool config::esp::ShowWeapon = TRUE;

int config::esp::bar::offset_x = -25;
int config::esp::bar::offset_y = 0;
int config::esp::bar::BarsPos = 1;        // 0 - top, 1 - left, 2 - bottom, 3 - right

int		config::esp::weapon::offset_x = 16;
int		config::esp::weapon::offset_y = 0;
bool	config::esp::weapon::custom_color = FALSE;
float	config::esp::weapon::color[3] = { 1, 0, 1 };

// hackstate

bool hackstate::ImGui_Init = FALSE;
bool hackstate::ImGui_Attached = FALSE;
bool hackstate::AimBotActive = FALSE;
bool hackstate::MenuActive = TRUE;