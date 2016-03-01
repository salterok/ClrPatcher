#pragma once

#include "stdafx.h"
#include "Patcher.h"
#include "Logger.h"


Patcher::Patcher()
{
}


Patcher::~Patcher()
{
}

HRESULT Patcher::ReplaceMethodRVA(const ModuleInfo &sourceModuleInfo, const mdMethodDef &source, const mdMethodDef &target)
{
	ULONG targetMethodRVA;
	DWORD implFlags;
	HRESULT hr = sourceModuleInfo.m_pImport->GetRVA(target, &targetMethodRVA, &implFlags);


	LOG_IFFAILEDRET(hr, L"ERROR getting target method RVA");

	hr = sourceModuleInfo.m_pEmit->SetRVA(source, targetMethodRVA);
	LOG_IFFAILEDRET(hr, L"ERROR setting source method RVA");
	LOG_APPEND(L"RVA set successfully");
	return S_OK;
}
