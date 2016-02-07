#pragma once
#include "ProfilerDTOTypes.h"

class Patcher
{
public:
	Patcher();
	~Patcher();

	/* Replace source method RVA with target method RVA
	* Only works for pure method or if method access accessible base(NOT overrided) members
	*/
	HRESULT ReplaceMethodRVA(const ModuleInfo &sourceModuleInfo, const mdMethodDef &source, const mdMethodDef &target);



};

