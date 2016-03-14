#include "stdafx.h"
#include "PatcherApi.h"
#include "SessionTypes.h"

namespace PatcherCore {

	void PatcherApi::replaceMethodRVA(const MemberPath & target, const MemberPath & source)
	{

		// IMetaDataEmit * pEmit,
		// IMetaDataAssemblyImport * pAssemblyImport


		mdMethodDef sourceM, targetM;
		ModuleInfo sourceModuleInfo, targetModuleInfo;

		BOOL sourceFound = GetMethodsInfoFromNames(
			Modules,
			source.ModuleName.c_str(),
			source.TypeName.c_str(),
			source.MemberName.c_str(),
			&sourceM,
			&sourceModuleInfo
			);
		BOOL targetFound = GetMethodsInfoFromNames(
			Modules,
			target.ModuleName.c_str(),
			target.TypeName.c_str(),
			target.MemberName.c_str(),
			&targetM,
			&targetModuleInfo
			);

		if (sourceFound && targetFound)
		{
			// for now sourceModule and targetModule are the same


			ULONG sourceMethodRVA;
			DWORD implFlags;
			HRESULT hr = sourceModuleInfo.m_pImport->GetRVA(sourceM, &sourceMethodRVA, &implFlags);

			if (FAILED(hr))
				ERR_APPEND(L"ERROR getting target method RVA");

			hr = sourceModuleInfo.m_pEmit->SetRVA(targetM, sourceMethodRVA);
			if (FAILED(hr))
				ERR_APPEND(L"ERROR setting source method RVA");

			LOG_APPEND(L"RVA set successfully");
		}
		else {
			ERR_APPEND(L"ERROR: Module, class, or function not found. Maybe module is not loaded yet?");
		}
	}


	// [private] Returns TRUE iff wszContainer ends with wszProspectiveEnding (case-insensitive).
	BOOL ContainsAtEnd(LPCWSTR wszContainer, LPCWSTR wszProspectiveEnding)
	{
		size_t cchContainer = wcslen(wszContainer);
		size_t cchEnding = wcslen(wszProspectiveEnding);

		if (cchContainer < cchEnding)
			return FALSE;

		if (cchEnding == 0)
			return FALSE;

		if (_wcsicmp(
			wszProspectiveEnding,
			&(wszContainer[cchContainer - cchEnding])) != 0)
		{
			return FALSE;
		}

		return TRUE;
	}


	BOOL PatcherApi::GetMethodsInfoFromNames(IDToInfoMap<ModuleID, ModuleInfo> * mMap, LPCWSTR wszModule, LPCWSTR wszClass, LPCWSTR wszFunction,
		mdMethodDef *methodDef, ModuleInfo *moduleInfo)

	{
		HRESULT hr = -1;
		HCORENUM hEnum = NULL;
		ULONG cMethodDefsReturned = 0;
		mdTypeDef typeDef;
		mdMethodDef rgMethodDefs[2];

		// Find all modules matching the name in this script entry.
		ModuleIDToInfoMap::LockHolder lockHolder(mMap);

		ModuleIDToInfoMap::Const_Iterator iterator;
		for (iterator = mMap->Begin(); (iterator != mMap->End()); iterator++)
		{
			LPCWSTR wszModulePathCur = &(iterator->second.m_wszModulePath[0]);

			// Only matters if we have the right module name.
			if (ContainsAtEnd(wszModulePathCur, wszModule))
			{
				hr = iterator->second.m_pImport->FindTypeDefByName(wszClass, mdTypeDefNil, &typeDef);

				if (FAILED(hr))
				{
					LOG_APPEND(L"Failed to find class '" << wszClass << L"',  hr = " << HEX(hr));
					continue;
				}

				hr = iterator->second.m_pImport->EnumMethodsWithName(
					&hEnum,
					typeDef,
					wszFunction,
					rgMethodDefs,
					_countof(rgMethodDefs),
					&cMethodDefsReturned);

				if (FAILED(hr) || (hr == S_FALSE))
				{
					LOG_APPEND(L"Found class '" << wszClass << L"', but no member methods with name '" <<
						wszFunction << L"', hr = " << HEX(hr));
					continue;
				}

				if (cMethodDefsReturned != 1)
				{
					LOG_APPEND(L"Expected exactly 1 methodDef to match class '" << wszClass << L"', method '" <<
						wszFunction << L"', but actually found '" << cMethodDefsReturned << L"'");
					continue;
				}

				// Save the matching pair.
				*methodDef = rgMethodDefs[0];
				*moduleInfo = iterator->second;

				// break loop if found methodDef
				hr = 0;
				break;
			}
		}

		// Return whether creation was successful.
		return hr == 0;
	}


	HRESULT PatcherApi::_ReplaceMethodRVA(const ModuleInfo &sourceModuleInfo, const mdMethodDef &source, const mdMethodDef &target)
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

}

