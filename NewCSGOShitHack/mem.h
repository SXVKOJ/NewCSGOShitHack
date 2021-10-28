#pragma once

static struct MEM
{
	char* SigScan(char* pattern, char* mask, char* begin, unsigned int size);

	DWORD FindPattern(char* base, char* pattern, char* mask);

	MODULEINFO GetModuleInfo(char* szModule);

	void InitOffsets();
} Mem;

class FnvHash
{
	static const unsigned int FNV_PRIME = 16777619u;
	static const unsigned int OFFSET_BASIS = 2166136261u;

	template <unsigned int N>
	static constexpr unsigned int fnvHashConst(const char(&str)[N], unsigned int I = N)
	{
		return I == 1 ? (OFFSET_BASIS ^ str[0]) * FNV_PRIME : (fnvHashConst(str, I - 1) ^ str[I - 1]) * FNV_PRIME;
	}

	static unsigned int fnvHash(const char* str)
	{
		const size_t length = strlen(str) + 1;
		unsigned int hash = OFFSET_BASIS;
		for (size_t i = 0; i < length; ++i)
		{
			hash ^= *str++;
			hash *= FNV_PRIME;
		}
		return hash;
	}

	struct Wrapper
	{
		Wrapper(const char* str) : str(str) { }
		const char* str;
	};

	unsigned int hash_value;
public:
	FnvHash(Wrapper wrapper) : hash_value(fnvHash(wrapper.str)) { }

	template <unsigned int N>
	constexpr FnvHash(const char(&str)[N]) : hash_value(fnvHashConst(str)) { }

	constexpr operator unsigned int() const { return this->hash_value; }
};

class RecvTable
{
public:

	RecvProp* m_pProps;
	int            m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool        m_bInitialized;
	bool        m_bInMainList;
};

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