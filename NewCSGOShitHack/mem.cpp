#include "includes.h"

MODULEINFO Mem::GetModuleInfo(char * szModule)
{
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandle((LPCSTR)szModule);

    if (hModule == 0)
    {
        return modInfo;
    }

    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

    return modInfo;
}

DWORD Mem::SigScan(char* module, char* pattern, char* mask)
{
    MODULEINFO mInfo = GetModuleInfo(module);

    DWORD base = (DWORD)mInfo.lpBaseOfDll;
    DWORD size = (DWORD)mInfo.SizeOfImage;

    DWORD patternLength = (DWORD)strlen(mask);

    for (DWORD i = 0; i < size - patternLength; i++)
    {
        bool found = true;

        for (DWORD j = 0; j < patternLength; j++)
        {
            found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
        }

        if (found)
            return base + i;
    }

    return NULL;
}

void Mem::UpdateOffsets()
{
    system("dumper.bat");
}