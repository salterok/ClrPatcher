#include "stdafx.h"
#include "Logger.h"

std::wofstream g_wLogFile;
std::wofstream g_wResultFile;
BOOL g_fLogFilePathsInitiailized = FALSE;

// I read this file written by GUI to tell me what to do
WCHAR g_wszCmdFilePath[MAX_PATH] = { L'\0' };

// I write to this file to respond to the GUI
WCHAR g_wszResponseFilePath[MAX_PATH] = { L'\0' };

// I write additional diagnostic info to this file
WCHAR g_wszLogFilePath[MAX_PATH] = { L'\0' };

// I write the human-readable profiling results to this (HTML) file
WCHAR g_wszResultFilePath[MAX_PATH] = { L'\0' };