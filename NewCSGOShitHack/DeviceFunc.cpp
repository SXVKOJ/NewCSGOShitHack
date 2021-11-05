#include "includes.h"

ID3DXLine* dx::lines::espLine		= nullptr;
ID3DXLine* dx::lines::espBoxLine	= nullptr;
ID3DXLine* dx::lines::HealthBarLine = nullptr;
ID3DXLine* dx::lines::ArmorBarLine  = nullptr;
LPD3DXFONT dx::fonts::health_font	= nullptr;
LPD3DXFONT dx::fonts::weapon_font	= nullptr;

VOID myDevice::InitFonts()
{
	D3DXCreateFont(pDevice, 18, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &dx::fonts::health_font);
	D3DXCreateFont(pDevice, 17, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &dx::fonts::weapon_font);
}

VOID myDevice::InitLines()
{
	D3DXCreateLine(pDevice, &dx::lines::espLine);
	D3DXCreateLine(pDevice, &dx::lines::espBoxLine);
	D3DXCreateLine(pDevice, &dx::lines::HealthBarLine);
	D3DXCreateLine(pDevice, &dx::lines::ArmorBarLine);
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