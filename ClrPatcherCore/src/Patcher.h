#pragma once
#include "ProfilerDTOTypes.h"
#include "PatcherApi.h"

namespace PatcherCore {
	struct Session;

	class Patcher : public PatcherApi
	{
	public:
		Patcher(Session *session);
		~Patcher();

		bool Patch();

	private:
		Session *m_session;

	};
}
