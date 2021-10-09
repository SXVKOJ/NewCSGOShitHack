#pragma once

static struct Mem
{
	DWORD SigScan(char* module, char* pattern, char* mask);

	MODULEINFO GetModuleInfo(char* szModule);

	void UpdateOffsets();
} MEM;