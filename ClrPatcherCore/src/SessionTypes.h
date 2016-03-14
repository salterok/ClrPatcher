#pragma once

#include <string>

using namespace std;
namespace PatcherCore {

	class PatcherApi;

	struct MemberPath
	{
		wstring ModuleName;
		wstring TypeName;
		wstring MemberName;
	};

	struct TypePath
	{
		wstring ModuleName;
		wstring TypeName;
	};

	class BasicCommand {
	public:
		virtual void run(PatcherApi &patcher) = 0;
	};

	class ReplaceMethodRVACommand : public BasicCommand {
	public:

		MemberPath Target;
		MemberPath Source;


		void run(PatcherApi &patcher);
	};
	
}
