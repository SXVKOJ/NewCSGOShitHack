#pragma once
#include "includes.h"

static class myDevice
{
private:
	LPDIRECT3DDEVICE9 pDevice;
public:
	VOID SetD3DDevice(LPDIRECT3DDEVICE9 pDevice);
	VOID InitFonts();
	VOID InitLines();

	VOID DrawRect(int x, int y, int w, int h, D3DCOLOR color);
	VOID DrawBox(float x, float y, float w, float h, float px, D3DCOLOR color);
	VOID DrawLine(ID3DXLine* _Line, float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color);
	VOID DrawMessage(LPD3DXFONT& font, unsigned int x, unsigned int y, D3DCOLOR color, LPCSTR Message);

	HWND Window;
	HWND GetProcessWindow();
} mDevice;