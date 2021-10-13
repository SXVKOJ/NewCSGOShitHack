#include "includes.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
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

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);

	return;
}

HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ImGui_Init)
	{
		InitImGui(pDevice);
		Hack.SetCustomImGuiStyle();

		ImGui_Init = true;
	}

	if (GetAsyncKeyState(Config.MenuHotKey) & 1)
		Config.MenuActive = !Config.MenuActive;

	if (Config.MenuActive)
		Hack.MenuThread();

	if (Config.WallHackESP)
		Hack.DXESPThread(pDevice);

	ImGui::SetMouseCursor(ImGuiMouseCursor_None);

	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	ImGuiIO& io = ImGui::GetIO();

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		break;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		break;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		break;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		break;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		break;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 1.0f : -1.0f;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		break;
	case WM_KEYDOWN:
		if (wParam == 52)
			break;
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		break;
	case WM_KEYUP:
		if (wParam == 52)
			break;
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		break;
	case WM_CHAR:
		if (wParam > 0 && wParam < 0x10000)
			io.AddInputCharacter((unsigned short)wParam);
		return true;
	}

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
			ImGui_Attached = true;
		}
	} while (!ImGui_Attached);

	return TRUE;
}

DWORD WINAPI MainThread(HMODULE hModule)
{
    MEM.UpdateOffsets();

	FILE* pFile = nullptr;
	
	if (Config.console)
		pFile = Console.Init();

    while (!GetAsyncKeyState(Config.EndHotKey))
    {
		Hack.MainThread();

		Sleep(Config.Delay);
    }

	kiero::shutdown();
	
	if (Config.console && pFile != nullptr)
		Console.Release(pFile);

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)KieroInit, hModule, NULL, NULL));
		CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}

    return TRUE;
}

