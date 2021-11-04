#pragma once

#include "kiero/kiero.h"
#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_internal.h"
#include "dear_imgui/imgui_impl_dx9.h"
#include "dear_imgui/imgui_impl_win32.h"
#include "kiero/minhook/include/MinHook.h"

#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "DearImGui.h"
#include "offsets.h"
#include "Client.hpp"
#include "Vector.h"
#include "Player.hpp"
#include "constvars.hpp"
#include "config.hpp"
#include "weapons.h"
#include "fEngine.h"
#include "VMT.h"
#include "HackFunc.h"

#define WINDOW_NAME "Dear ImGui DirectX9 Example"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);