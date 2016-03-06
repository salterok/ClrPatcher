#include "stdafx.h"
#include "PatcherSession.h"
#include "yaml-cpp/yaml.h"


using namespace std;
using namespace YAML;
using namespace Const::CommandSyntax;

namespace PatcherSession {

	DocType _documentType(const string &type) {
		if (type == DOC_TYPE_COMMANDS)
			return DocType::COMMANDS;

		return DocType::UNKNOWN;
	}


	Session _parse(std::vector<Node> &docs)
	{
		Session session;
		LOG_APPEND("Documents found: " << docs.size());

		for(auto doc : docs)
		{
			LOG_APPEND("_parse " << doc["doc_type"].as<string>().c_str());
			if (!doc.IsMap())
				throw new exception("Patcher commands should contain only documents of map");
			auto docType = doc[DOC_TYPE_EL];
			if (docType.IsDefined() && docType.IsScalar()) {
				DocType type = _documentType(docType.Scalar());
				switch (type)
				{
				case COMMANDS:
					LOG_APPEND("COMMAND section in YAML found");
					break;
				case UNKNOWN:
				default:
					break;
				}
			}
			else
				throw new exception("doo");
		}

		return session;
	}

	Session _parseFromString(char * commands)
	{
		auto docs = YAML::LoadAll(commands);
		return _parse(docs);
	}

	Session _parseFromFile(const std::string commandsFile)
	{
		LOG_APPEND("Reading session from file: " << commandsFile.c_str());
		auto docs = YAML::LoadAllFromFile(commandsFile);
		return _parse(docs);
	}

	bool tryLoadSession(Session * session)
	{
		try {
			char buffer[Const::MAX_PATCHER_COMMAND_LENGTH];
			size_t maxCommandSize = Const::MAX_PATCHER_COMMAND_LENGTH;
			errno_t result = getenv_s(&maxCommandSize, buffer, Const::PATCHER_COMMAND);

			if (result == 0 && maxCommandSize > 0) {
				*session = parseFromString(buffer);
				return true;
			}
			else {
				maxCommandSize = MAX_PATH;
				result = getenv_s(&maxCommandSize, buffer, Const::PATCHER_COMMAND_FILEPATH);
				LOG_APPEND("READ: " << maxCommandSize << " : " << result << "| ");
				if (result == 0 && maxCommandSize > 0) {
					std::string file(buffer, maxCommandSize);
					*session = parseFromFile(file);
					return true;
				}
				// m_isInitialized stay false
			}
		}
		catch (YAML::Exception ex) {
			LOG_APPEND(ex.what() << " | " << ex.msg.c_str());
		}
		catch (std::exception &ex) {
			LOG_APPEND(ex.what());
			// TODO: add logs
		}
		catch (...) {
			LOG_APPEND("EX");
		}
		return false;
	}

};




