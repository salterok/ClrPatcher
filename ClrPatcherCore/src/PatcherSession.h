#pragma once

#include "SessionTypes.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;
namespace PatcherCore {

	struct Options
	{

	};

	typedef vector<BasicCommand*> Commands;

	struct Session
	{
		int version;
		Options options;
		Commands commands;
	};

	enum SectionType
	{
		UNKNOWN,
		VERSION,
		OPTIONS,
		COMMANDS
	};

	Session parseFromString(char *commands);
	Session parseFromFile(const std::string commandsFile);
	bool tryLoadSession(Session *session);
};

