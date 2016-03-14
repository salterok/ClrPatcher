#pragma once

#include "stdafx.h"
#include "Patcher.h"
#include "Logger.h"
#include "PatcherSession.h"

using namespace PatcherCore;

Patcher::Patcher(Session *session)
{
	m_session = session;
}

Patcher::~Patcher()
{
}

bool Patcher::Patch()
{
	// TODO: add try-catch
	for (auto command : m_session->commands) {
		command->run(*this);
	}


	LOG_APPEND("replacing rva");



	return false;
}

