#include "includes.h"

DWORD WINAPI MainThread(HMODULE hModule)
{
    MEM.UpdateOffsets();

    // FILE * pFile = Console.Init();

    while (!GetAsyncKeyState(VK_END))
    {
        Hack.MainThread();
    }

    // Console.Release(pFile);

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

