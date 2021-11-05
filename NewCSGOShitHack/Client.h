#pragma once
#include "includes.h"

#define CLIENT (uintptr_t)GetModuleHandle("client.dll")
#define ENGINE (uintptr_t)GetModuleHandle("engine.dll")
#define CLIENTSTATE *(uintptr_t*)(ENGINE + offsets::dwClientState)