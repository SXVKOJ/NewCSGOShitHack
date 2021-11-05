#include "includes.h"

static class DearImGui
{
private:
	LPDIRECT3DDEVICE9 pDevice;
public:
	VOID SetD3DDevice(LPDIRECT3DDEVICE9 pDevice);

	VOID Init();
	VOID Draw();
	VOID SetCustomStyle();
} dImGui;