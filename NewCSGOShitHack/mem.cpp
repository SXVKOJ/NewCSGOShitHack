#include "includes.h"

/*
class RecvProp
{
public:
    char* m_pVarName;
    void* m_RecvType;
    int                     m_Flags;
    int                     m_StringBufferSize;
    int                     m_bInsideArray;
    const void* m_pExtraData;
    RecvProp* m_pArrayProp;
    void* m_ArrayLengthProxy;
    void* m_ProxyFn;
    void* m_DataTableProxyFn;
    RecvTable* m_pDataTable;
    int                     m_Offset;
    int                     m_ElementStride;
    int                     m_nElements;
    const char* m_pParentArrayPropName;
};

class RecvTable
{
public:
    RecvProp *m_pProps;
    int            m_nProps;
    void* m_pDecoder;
    char* m_pNetTableName;
    bool        m_bInitialized;
    bool        m_bInMainList;
};

class ClientClass
{
public:
    void* m_pCreateFn;
    void* m_pCreateEventFn;
    char* m_pNetworkName;
    RecvTable* m_pRecvTable;
    ClientClass* m_pNext;
    int                m_ClassID;
};

uintptr_t GetAllClassesOffset()
{
    uintptr_t Offset = Mem.FindPattern((char*)"cliend.dll", (char*)"A1 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC A1 ? ? ? ? B9", (char*)"xxxxxxxxxxxxxxxxxxxxxx");
}

MODULEINFO MEM::GetModuleInfo(char * szModule)
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

// mask - num of bytes x
char* MEM::SigScan(char* pattern, char* mask, char* begin, unsigned int size)
{
    unsigned int patternLength = strlen(mask);

    for (unsigned int i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for (unsigned int j = 0; j < patternLength; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }
    return nullptr;
}

uintptr_t MEM::FindPattern(char* base, char* pattern, char* mask)
{
    size_t patternLength = strlen(mask);

    MODULEINFO mInfo = GetModuleInfo(base);

    uintptr_t base = (uintptr_t)mInfo.lpBaseOfDll;
    uintptr_t size = (uintptr_t)mInfo.SizeOfImage;

    for (uintptr_t i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for (uintptr_t j = 0; j < patternLength; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j))
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            return (uintptr_t)base + i;
        }
    }
    return 0;
}

uintptr_t GetOffset(RecvTable* table, const char* tableName, const char* netvarName)
{
    for (int i = 0; i < table->m_nProps; i++)
    {
        RecvProp prop = table->m_pProps[i];

        if (!_stricmp(prop.m_pVarName, netvarName))
        {
            return prop.m_Offset;
        }

        if (prop.m_pDataTable)
        {
            uintptr_t offset = GetOffset(prop.m_pDataTable, tableName, netvarName);

            if (offset)
            {
                return offset + prop.m_Offset;
            }
        }
    }
    return 0;
}

uintptr_t GetNetVarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass)
{
    ClientClass* currNode = clientClass;

    for (auto currNode = clientClass; currNode; currNode = currNode->m_pNext)
    {
        if (!_stricmp(tableName, currNode->m_pRecvTable->m_pNetTableName))
        {
            return GetOffset(currNode->m_pRecvTable, tableName, netvarName);
        }
    }

    return 0;
}

void MEM::InitOffsets() 
{
    using namespace offsets;

    ClientClass *clientClass = (ClientClass*)(Game.GetClient() + GetAllClassesOffset());
}*/