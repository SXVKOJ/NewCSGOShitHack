#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1
#pragma once
#include "kiero/kiero.h"
#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_internal.h"
#include "dear_imgui/imgui_impl_dx9.h"
#include "dear_imgui/imgui_impl_win32.h"
#include "kiero/minhook/include/MinHook.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>
#include <winternl.h>
#include <cmath>
#include <string>
#include <vector>

#include "HackFunc.h"
#include "Game.h"

#include "constVars.hpp"
#include "image.hpp"
#include "Config.hpp"
#include "offsets.hpp"
#include "Vector.h"
#include "mem.h"

#define WINDOW_NAME "Dear ImGui DirectX9 Example"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);