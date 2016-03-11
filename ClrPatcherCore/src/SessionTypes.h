#pragma once

#include "PatcherApi.h"
#include <string>

using namespace std;
namespace PatcherCore {

	class BasicCommand {
	public:
		virtual HRESULT run(PatcherApi &patcher) = 0;
	};

	class ReplaceMethodRVACommand : public BasicCommand {
	public:
		string TargetMethod;
		string DonorMethod;

		HRESULT run(PatcherApi &patcher);
	};
	
}
