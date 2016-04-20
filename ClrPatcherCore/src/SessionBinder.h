#pragma once

#include "PatcherSession.h"
#include "yaml-cpp/yaml.h"

namespace YAML {
#define CONVERTER_DECL(className) \
	template<> \
	struct convert<className> { \
		static Node encode(const className &); \
		static bool decode(const Node &, className &); \
	}; \

#define CONVERTER_ENCODE(className, targetName) \
	static Node convert<className>::encode(const className &targetName) \

#define CONVERTER_DECODE(className, nodeName, targetName) \
	bool convert<className>::decode(const Node &nodeName, className &targetName) \


	CONVERTER_DECL(PatcherCore::Session)
	CONVERTER_DECL(PatcherCore::ReplaceMethodRVACommand*)



	//template<>
	//struct convert<Session> {
	//	static Node encode(const Session &session);
	//	static bool decode(const Node &node, Session &session);
	//};



}

using namespace YAML;
namespace PatcherCore {

	void assertIsScalar(const Node &node);
	void assertIsSequence(const Node &node);
	void assertIsMap(const Node &node);
	bool readProperty(const Node &node, string propName, string &prop);


	MemberPath readMemberPath(string prefix, const Node &node);
	TypePath readTypePath(string prefix, const Node &node);

}
