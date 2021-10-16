#include "includes.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ID3DXLine* DXLines::p_Line = nullptr;
ID3DXLine* DXLines::Line = nullptr;

ID3DXLine* DXLines::BodyLine = nullptr;
ID3DXLine* DXLines::rLegLine = nullptr;
ID3DXLine* DXLines::lLegLine = nullptr;
ID3DXLine* DXLines::rArmLine = nullptr;
ID3DXLine* DXLines::lArmLine = nullptr;

IDirect3DTexture9* tImage = nullptr;
LPD3DXFONT m_font = NULL;
EndScene oEndScene = NULL;
WNDPROC oWndProc;

static FrameStageNotify fnFrameStageNotify;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();

	D3DDEVICE_CREATION_PARAMETERS CP;
	pDevice->GetCreationParameters(&CP);
	window = CP.hFocusWindow;

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontDefault();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	
	D3DVIEWPORT9 viewport;
	viewport.Width = io.DisplaySize.x;
	viewport.Height = io.DisplaySize.y;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	viewport.X = 0.0f;
	viewport.Y = 0.0f;
	pDevice->SetViewport(&viewport);

	D3DXCreateFont(pDevice, 16, 6, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &m_font);

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);

	return;
}

HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!config::ImGui_Init)
	{
		InitImGui(pDevice);
		Hack.SetCustomImGuiStyle();
		Hack.LoadImageToDll(NameArry, pDevice);
		Hack.InitLines(pDevice);

		config::ImGui_Init = true;
	}

	if (GetAsyncKeyState(config::MenuHotKey) & 1)
		config::MenuActive = !config::MenuActive;

	if (config::MenuActive)
		Hack.MenuThread();

	if (config::WallHackESP)
		Hack.DXESPThread();

	if (config::esp::ESPBones)
		Hack.ESPDrawBonesThread();

	return oEndScene(pDevice);
}

void __fastcall FrameStageNotifyThink(void* ecx, void* edx, ClientFrameStage_t Stage)
{
	if (Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (config::CurrentSkinID != 0 && Game.GetCurrentWeapon() != -1)
			Hack.ChangeSkin(Game.GetCurrentWeapon(), config::CurrentSkinID);
	}

	fnFrameStageNotify(ecx, Stage);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	ImGuiIO& io = ImGui::GetIO();

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE;

	window = handle;
	return FALSE;
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

DWORD WINAPI InitVMTHook(HMODULE hModule)
{
	VMTHook* Client_Table = nullptr;

	void* client = (void*)GetInterface("client.dll", "VClient018");
	Client_Table = new VMTHook(client);

	Client_Table->SwapPointer(36, &FrameStageNotifyThink);

	Client_Table->ApplyNewTable();

	return TRUE;
}

DWORD WINAPI KieroInit(HMODULE hModule)
{
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&oEndScene, hkEndScene);

			do {
				window = GetProcessWindow();
			} while (window == NULL);

			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			config::ImGui_Attached = true;
		}
	} while (!config::ImGui_Attached);

	return TRUE;
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    MEM.UpdateOffsets();

	FILE* pFile = nullptr;
	
	if (config::console)
		pFile = Console.Init();

    while (!GetAsyncKeyState(config::EndHotKey))
    {
		Hack.MainThread();

		if (config::MainThreadDelay > 1)
			Sleep(config::MainThreadDelay);
    }

	kiero::shutdown();
	
	if (config::console && pFile != nullptr)
		Console.Release(pFile);

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitVMTHook, hModule, NULL, NULL));
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)KieroInit, hModule, NULL, NULL));
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL));
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}

    return TRUE;
}

