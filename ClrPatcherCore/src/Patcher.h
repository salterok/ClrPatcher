#pragma once
#include "ProfilerDTOTypes.h"
#include "PatcherSession.h"
#include "PatcherApi.h"


namespace PatcherCore {
	class Patcher
	{
	public:
		Patcher(Session session);
		~Patcher();

	private:
		Session m_session;

	};
}
