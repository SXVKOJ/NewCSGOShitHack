#include "includes.h"

VOID myDevice::InitFonts()
{
	D3DXCreateFont(pDevice, 18, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &health_font);
	D3DXCreateFont(pDevice, 17, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &weapon_font);
}

VOID myDevice::InitLines()
{
	D3DXCreateLine(pDevice, &espLine);
	D3DXCreateLine(pDevice, &espBoxLine);

	D3DXCreateLine(pDevice, &BodyLine);
	D3DXCreateLine(pDevice, &rLegLine);
	D3DXCreateLine(pDevice, &lLegLine);
	D3DXCreateLine(pDevice, &rArmLine);
	D3DXCreateLine(pDevice, &lArmLine);

	D3DXCreateLine(pDevice, &HealthBarLine);
	D3DXCreateLine(pDevice, &ArmorBarLine);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE;

	mDevice.Window = handle;
	return FALSE;
}

HWND myDevice::GetProcessWindow()
{
	mDevice.Window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return mDevice.Window;
}