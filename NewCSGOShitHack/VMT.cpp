#include "includes.h"

void* GetInterface(const char* dllname, const char* interfacename)
{
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(dllname), "CreateInterface");

	int returnCode = 0;
	void* xinterface = CreateInterface(interfacename, &returnCode);

	return xinterface;
}