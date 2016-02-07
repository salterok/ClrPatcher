#pragma once

#include <fstream>
#include <iostream>
#include <share.h>
#include <vector>
#include <windows.h>
#include <io.h>
#include <dos.h>
#include <Windows.h>


// String for mscorlib methods or not.
#define MSCORLIBCOMMAND L"Inserting into mscorlib: %c\r\n"

// Command strings for communicating out-of-process.
#define CMD_REJITFUNC L"pf"
#define CMD_REVERTFUNC L"rf"
#define CMD_QUIT L"qa"

// Response strings for communicating out-of-process.
#define RSP_REJITSUCCESS L"ps"
#define RSP_REVERTSUCCESS L"rs"
#define RSP_REJITFAILURE L"pf"
#define RSP_REVERTFAILURE L"rf"
#define RSP_QUITSUCCESS L"qs"


extern std::wofstream g_wLogFile;
extern std::wofstream g_wResultFile;
extern BOOL g_fLogFilePathsInitiailized;

// I read this file written by GUI to tell me what to do
extern WCHAR g_wszCmdFilePath[MAX_PATH];

// I write to this file to respond to the GUI
extern WCHAR g_wszResponseFilePath[MAX_PATH];

// I write additional diagnostic info to this file
extern WCHAR g_wszLogFilePath[MAX_PATH];

// I write the human-readable profiling results to this (HTML) file
extern WCHAR g_wszResultFilePath[MAX_PATH];

#define HEX(HR) L"0x" << std::hex << std::uppercase << HR << std::dec
#define RESULT_APPEND(EXPR) do { g_wResultFile.open(g_wszResultFilePath, std::ios::app); g_wResultFile << L"\n" << EXPR; g_wResultFile.close(); } while(0)
#define RESPONSE_LITERAL(EXPR) do { std::wofstream ofsLog; ofsLog.open(g_wszResponseFilePath, std::ios::app); ofsLog << EXPR; ofsLog.close(); } while(0)
#define RESPONSE_APPEND(EXPR) RESPONSE_LITERAL(g_nLastRefid << L">" << EXPR << L"\n")
#define RESPONSE_IS(REFID, EXPR, MODULE, CLASS, FUNC) RESPONSE_LITERAL(REFID << L">" << EXPR << L"\t" << MODULE << L"\t" << CLASS << L"\t" << FUNC << L"\n")
#define RESPONSE_ERROR(EXPR) RESPONSE_APPEND(L"ERROR\tError: " << EXPR)
#define LOG_APPEND(EXPR) do { g_wLogFile.open(g_wszLogFilePath, std::ios::app); g_wLogFile << L"\n" << EXPR; g_wLogFile.close(); } while(0)
#define LOG_IFFAILEDRET(HR, EXPR) do { if (FAILED(HR)) { LOG_APPEND(EXPR << L", hr = " << HEX(HR)); return HR; } } while(0)


