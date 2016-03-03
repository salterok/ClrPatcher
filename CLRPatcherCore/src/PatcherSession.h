#pragma once

#include <fstream>
#include <string>
#include <vector>


namespace PatcherSession {

	enum DocType
	{
		UNKNOWN,
		COMMANDS
	};

	struct Session
	{

	};

	Session ParseFromString(char *commands);
	Session ParseFromFile(const std::string commandsFile);
};
