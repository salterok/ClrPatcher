#pragma once
#include "ProfilerDTOTypes.h"

namespace PatcherCore {
	struct MemberPath;

	class PatcherApi {

	public:
		ICorProfilerInfo2 *ProfilerInfo;
		IDToInfoMap<ModuleID, ModuleInfo> * Modules;

	


#pragma region API




		BOOL GetMethodsInfoFromNames(IDToInfoMap<ModuleID, ModuleInfo> * mMap, LPCWSTR wszModule, LPCWSTR wszClass, LPCWSTR wszFunction,
			mdMethodDef *methodDef, ModuleInfo *moduleInfo);



		/* Replace source method RVA with target method RVA
		* Only works for pure method or if method access accessible base(NOT overrided) members
		*/
		void replaceMethodRVA(const MemberPath &target, const MemberPath &donor);
		HRESULT _ReplaceMethodRVA(const ModuleInfo &sourceModuleInfo, const mdMethodDef &source, const mdMethodDef &target);

		void ReplaceClass(LPCWSTR moduleName, LPCWSTR sourceClassName, LPCWSTR replaceClassName);


#pragma endregion
	};
}
