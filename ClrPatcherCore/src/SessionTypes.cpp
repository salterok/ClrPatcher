#include "stdafx.h"
#include "SessionTypes.h"
#include "PatcherApi.h"

namespace PatcherCore {
	void ReplaceMethodRVACommand::run(PatcherApi & patcher)
	{
		
		patcher.replaceMethodRVA(Target, Source);

		
	}
}