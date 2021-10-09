#include "includes.h"

FILE* CONSOLE::Init()
{
	FILE* pFile = nullptr;

	AllocConsole();
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	return pFile;
}

void CONSOLE::Release(FILE * filePtr)
{
	fclose(filePtr);

	FreeConsole();
}