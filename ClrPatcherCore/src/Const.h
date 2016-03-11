#pragma once

namespace Const {
	static const size_t MAX_PATCHER_COMMAND_LENGTH = 1024;
	static const char *PATCHER_COMMAND = "PATCHER_COMMAND";
	static const char *PATCHER_COMMAND_FILEPATH = "PATCHER_COMMAND_FILEPATH";



	namespace CommandSyntax {
		static const char *SECTION_TYPE_OPTIONS = "options";
		static const char *SECTION_TYPE_COMMANDS = "commands";
	}
}

