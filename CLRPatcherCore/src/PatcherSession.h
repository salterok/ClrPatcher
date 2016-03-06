#pragma once

#include <fstream>
#include <string>
#include <vector>


namespace PatcherSession {

	enum DocType
	{
		UNKNOWN,
		OPTIONS,
		COMMANDS
	};

	struct Session
	{

	};


	bool tryLoadSession(Session *session);
	Session parseFromString(char *commands);
	Session parseFromFile(const std::string commandsFile);
};
