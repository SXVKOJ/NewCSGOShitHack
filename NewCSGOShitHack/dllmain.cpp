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

ID3DXLine* DXLines::HealthBarLine = nullptr;
ID3DXLine* DXLines::ArmorBarLine = nullptr;

IDirect3DTexture9* tImage = nullptr;

LPD3DXFONT m_font = NULL;
LPD3DXFONT weapon_font = NULL;

EndScene oEndScene = NULL;
WNDPROC oWndProc;

static HWND window = NULL;

typedef void(_stdcall* FrameStageNotify)(ClientFrameStage_t Stage);
typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);
FrameStageNotify oFrameStageNotify = NULL;

void* GetInterface(const char* dllname, const char* interfacename)
{
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(dllname), "CreateInterface");

	int returnCode = 0;
	void* xinterface = CreateInterface(interfacename, &returnCode);

	return xinterface;
}

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

	D3DXCreateFont(pDevice, 18, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &m_font);
	D3DXCreateFont(pDevice, 17, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &weapon_font);

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
		Hack.InitLines(pDevice);

		config::ImGui_Init = true;
	}

	if (GetAsyncKeyState(config::HotKeys::Menu) & 1)
		config::MenuActive = !config::MenuActive;

	if (config::MenuActive)
		Hack.MenuThread();

	if (config::WallHackESP)
		Hack.DXESPThread();

	if (config::esp::ESPBones)
		Hack.ESPDrawBonesThread();

	return oEndScene(pDevice);
}

void __stdcall hkFrameStageNotify(ClientFrameStage_t Stage)
{	
	if (Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		Hack.SkinChangerThread();
	}
	oFrameStageNotify(Stage);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

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
	void* _Client = GetInterface("client.dll", "VClient018");

	DWORD* _clientVTable = (*reinterpret_cast<DWORD**>(_Client));

	oFrameStageNotify = (FrameStageNotify)_TrampHook32((char*)_clientVTable[37], (char*)hkFrameStageNotify, 9);

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
	FILE* pFile = nullptr;
	
	if (config::console)
		pFile = Console.Init();

    while (!GetAsyncKeyState(config::HotKeys::End))
    {
		Hack.MainThread();

		if (config::MainThreadDelay > 1 && config::FPSMode)
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
