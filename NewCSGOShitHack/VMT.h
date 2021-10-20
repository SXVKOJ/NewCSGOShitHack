#pragma once

#include <cstdint>
#include <Windows.h>

char* _TrampHook32(char* src, char* dst, unsigned int len);

enum ClientFrameStage_t {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

void* GetInterface(const char* dllname, const char* interfacename);
//void __stdcall FrameStageNotifyThink(ClientFrameStage_t Stage);