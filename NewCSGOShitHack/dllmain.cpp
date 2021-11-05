#include "includes.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
EndScene oEndScene = NULL;
WNDPROC oWndProc   = NULL;

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

HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!hackstate::ImGui_Init)
	{
		dImGui.SetD3DDevice(pDevice);
		mDevice.SetD3DDevice(pDevice);

		dImGui.Init();
		dImGui.SetCustomStyle();

		mDevice.InitFonts();
		mDevice.InitLines();

		hackstate::ImGui_Init = TRUE;
	}

	if (GetAsyncKeyState(config::HotKeys::Menu) & 1)
		hackstate::MenuActive = !hackstate::MenuActive;

	if (hackstate::MenuActive)
		dImGui.Draw();

	if (config::hack::WallHackESP)
		Hack.DXESPThread();

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
				mDevice.Window = mDevice.GetProcessWindow();
			} while (mDevice.Window == NULL);

			oWndProc = (WNDPROC)SetWindowLongPtr(mDevice.Window, GWL_WNDPROC, (LONG_PTR)WndProc);
			hackstate::ImGui_Attached = TRUE;
		}
	} while (!hackstate::ImGui_Attached);

	return TRUE;
}

DWORD WINAPI MainThread(HMODULE hModule)
{	
	while (!GetAsyncKeyState(config::HotKeys::End))
		Hack.MainThread();
		
	kiero::shutdown();

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitVMTHook, hModule, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)KieroInit, hModule, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
	}

    return TRUE;
}
