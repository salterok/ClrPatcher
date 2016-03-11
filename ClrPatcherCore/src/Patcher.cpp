#pragma once

#include "stdafx.h"
#include "Patcher.h"
#include "Logger.h"

using namespace PatcherCore;

Patcher::Patcher(Session session)
{
	m_session = session;
}

Patcher::~Patcher()
{
}

