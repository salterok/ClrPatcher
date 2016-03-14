#include "stdafx.h"
#include "Logger.h"

std::wofstream g_wLogFile;
BOOL g_fLogFilePathsInitiailized = FALSE;

WCHAR g_wszLogFilePath[MAX_PATH] = { L'\0' };
