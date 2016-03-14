#pragma once

#include <fstream>
#include <iostream>
#include <share.h>
#include <vector>
#include <windows.h>
#include <io.h>
#include <dos.h>
#include <Windows.h>

extern std::wofstream g_wLogFile;
extern BOOL g_fLogFilePathsInitiailized;

// I write additional diagnostic info to this file
extern WCHAR g_wszLogFilePath[MAX_PATH];

#define HEX(HR) L"0x" << std::hex << std::uppercase << HR << std::dec
#define LOG_APPEND(EXPR) do { g_wLogFile.open(g_wszLogFilePath, std::ios::app); g_wLogFile << L"\n" << EXPR; g_wLogFile.close(); } while(0)
#define ERR_APPEND(EXPR) do { g_wLogFile.open(g_wszLogFilePath, std::ios::app); g_wLogFile << L"\nERROR: " << EXPR; g_wLogFile.close(); } while(0)
#define LOG_IFFAILEDRET(HR, EXPR) do { if (FAILED(HR)) { LOG_APPEND(EXPR << L", hr = " << HEX(HR)); return HR; } } while(0)


