#include "includes.h"

static class DearImGui
{
public:
	LPDIRECT3DDEVICE9 pDevice;

	VOID Init();
	VOID Draw();
	VOID SetCustomStyle();
} dImGui;