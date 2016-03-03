#include "stdafx.h"
#include "PatcherSession.h"
#include "Const.h"
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


	Session _parse(std::vector<Node> docs)
	{
		Session session;
		for each (auto doc in docs)
		{
			if (!doc.IsMap())
				throw new exception("Patcher commands should contain only documents of map");
			auto docType = doc[DOC_TYPE_EL];
			if (docType.IsDefined() && docType.IsScalar()) {
				DocType type = _documentType(docType.Scalar());
				switch (type)
				{
				case COMMANDS:

					break;
				case UNKNOWN:
				default:
					break;
				}
			}
			else
				throw new exception();
		}

		return session;
	}

	Session ParseFromString(char * commands)
	{
		auto docs = YAML::LoadAll(commands);
		return _parse(docs);
	}

	Session ParseFromFile(const std::string commandsFile)
	{
		auto docs = YAML::LoadAllFromFile(commandsFile);
		return _parse(docs);
	}

};




