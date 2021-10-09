#pragma once
#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_dx9.h"
#include "dear_imgui/imgui_impl_win32.h"

#include "min_hook/include/MinHook.h"

#include "d3d9.h"
#include "d3dx9.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>
#include <winternl.h>
#include <cmath>

#include "HackFunc.h"
#include "Game.h"

#include "constVars.hpp"
#include "config.hpp"
#include "offsets.hpp"
#include "Vector.h"
#include "mem.h"