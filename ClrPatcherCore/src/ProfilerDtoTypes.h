#pragma once

#include "bootstrap/basehdr.h"
#include <map>

class CSHolder
{
public:
	CSHolder(CRITICAL_SECTION * pcs)
	{
		m_pcs = pcs;
		EnterCriticalSection(m_pcs);
	}

	~CSHolder()
	{
		assert(m_pcs != NULL);
		LeaveCriticalSection(m_pcs);
	}

private:
	CRITICAL_SECTION * m_pcs;
};

template <class _ID, class _Info>
class IDToInfoMap
{
public:
	typedef std::map<_ID, _Info> Map;
	typedef typename Map::iterator Iterator;
	typedef typename Map::const_iterator Const_Iterator;
	typedef typename Map::size_type Size_type;

	IDToInfoMap()
	{
		InitializeCriticalSection(&m_cs);
	}

	Size_type GetCount()
	{
		CSHolder csHolder(&m_cs);
		return m_map.size();
	}

	BOOL LookupIfExists(_ID id, _Info * pInfo)
	{
		CSHolder csHolder(&m_cs);
		Const_Iterator iterator = m_map.find(id);
		if (iterator == m_map.end())
		{
			return FALSE;
		}

		*pInfo = iterator->second;
		return TRUE;
	}

	_Info Lookup(_ID id)
	{
		CSHolder csHolder(&m_cs);
		_Info info;
		if (!LookupIfExists(id, &info))
		{
			g_wLogFile.open(g_wszLogFilePath, std::ios::app);
			g_wLogFile << L"\nIDToInfoMap lookup failed.";
			g_wLogFile.close();
		}

		return info;
	}

	void Erase(_ID id)
	{
		CSHolder csHolder(&m_cs);
		Size_type cElementsRemoved = m_map.erase(id);
		if (cElementsRemoved != 1)
		{
			g_wLogFile.open(g_wszLogFilePath, std::ios::app);
			g_wLogFile << L"\nIDToInfoMap: " << cElementsRemoved <<
				L" elements removed, 1 expected.";
			g_wLogFile.close();
		}
	}

	void Update(_ID id, _Info info)
	{
		CSHolder csHolder(&m_cs);
		m_map[id] = info;
	}

	Const_Iterator Begin()
	{
		return m_map.begin();
	}

	Const_Iterator End()
	{
		return m_map.end();
	}

	class LockHolder
	{
	public:
		LockHolder(IDToInfoMap<_ID, _Info> * pIDToInfoMap) :
			m_csHolder(&(pIDToInfoMap->m_cs))
		{
		}

	private:
		CSHolder m_csHolder;
	};

private:
	Map m_map;
	CRITICAL_SECTION m_cs;
};

typedef IDToInfoMap<mdMethodDef, int> MethodDefToLatestVersionMap;

struct ModuleInfo
{
	WCHAR                               m_wszModulePath[512];
	IMetaDataImport *                   m_pImport;
	IMetaDataEmit *						m_pEmit;
	mdToken                             m_mdEnterProbeRef;
	mdToken                             m_mdExitProbeRef;
	MethodDefToLatestVersionMap *       m_pMethodDefToLatestVersionMap;
};

typedef IDToInfoMap<ModuleID, ModuleInfo> ModuleIDToInfoMap;

template <class MetaInterface>
class COMPtrHolder
{
public:
	COMPtrHolder()
	{
		m_ptr = NULL;
	}

	~COMPtrHolder()
	{
		if (m_ptr != NULL)
		{
			m_ptr->Release();
			m_ptr = NULL;
		}
	}

	MetaInterface* operator->()
	{
		return m_ptr;
	}

	MetaInterface** operator&()
	{
		return &m_ptr;
	}

	operator MetaInterface*()
	{
		return m_ptr;
	}

private:
	MetaInterface* m_ptr;
};

// A single entry in the single-thread shadow stack
struct ShadowStackFrameInfo
{
	ModuleID m_moduleID;
	mdMethodDef m_methodDef;
	int m_nVersion;
	ULONGLONG m_ui64TickCountOnEntry;
};
