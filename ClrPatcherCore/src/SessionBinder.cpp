#include "stdafx.h"
#include "SessionBinder.h"

using namespace std;

namespace PatcherCore {

	inline void assertIsScalar(const Node & node)
	{
		if (!node.IsDefined() || !node.IsScalar())
			throw YAML::RepresentationException(node.Mark(),
				"Node must be defined and scalar type");
	}

	inline void assertIsSequence(const Node & node)
	{
		if (!node.IsDefined() || !node.IsSequence())
			throw YAML::RepresentationException(node.Mark(),
				"Node must be defined and sequence type");
	}

	inline void assertIsMap(const Node & node)
	{
		if (!node.IsDefined() || !node.IsMap())
			throw YAML::RepresentationException(node.Mark(),
				"Node must be defined and map type");
	}

	inline bool readProperty(const Node & node, string propName, wstring & prop)
	{
		Node param = node[propName];
		assertIsScalar(param);
		auto str = param.Scalar();

		// yaml-cpp claim that returned string is utf8 encoded internally
		// https://github.com/jbeder/yaml-cpp/wiki/Strings
		// so just assign internal buffer to wstring
		// 


		// TODO: fix convert to wstring
		prop.assign(str.begin(), str.end());



		// windows only!
		// 
		// #include <atlstr.h>
		// #include <atlconv.h>
		// 
		// ATL::CA2W g2(str.c_str());
		// LOG_APPEND("READ__2: " << g2.m_psz);

		return true;
	}

	MemberPath PatcherCore::readMemberPath(string prefix, const Node & node)
	{
		assertIsMap(node);

		MemberPath path;
		readProperty(node, prefix + "Module", path.ModuleName);
		readProperty(node, prefix + "Type", path.TypeName);
		readProperty(node, prefix + "Member", path.MemberName);

		return path;
	}

	TypePath PatcherCore::readTypePath(string prefix, const Node & node)
	{
		assertIsMap(node);

		TypePath path;
		readProperty(node, prefix + "Module", path.ModuleName);
		readProperty(node, prefix + "Type", path.TypeName);

		return path;
	}

}

using namespace PatcherCore;
namespace YAML {

	BasicCommand* parseCommandByType(const Node &node, string commandStringType) {
		if (commandStringType == "ReplaceMethodRVACommand")
			return node.as<ReplaceMethodRVACommand*>();

		string exMsg("Patcher does not support command: ");
		exMsg.append(commandStringType);
		throw new exception(exMsg.c_str());
	}

	// 
	bool convert<Session>::decode(const Node &node, Session &session) {
		assertIsMap(node);

		Node section = node[Const::CommandSyntax::SECTION_TYPE_OPTIONS];
		if (section.IsDefined() && section.IsMap()) {
			// todo: 
		}

		section = node[Const::CommandSyntax::SECTION_TYPE_COMMANDS];
		if (section.IsDefined() && section.IsSequence()) {
			vector<BasicCommand*> commands;
			for (auto fakeCommand = section.begin(); fakeCommand != section.end(); fakeCommand++) {

				// now we try to emulate list with key(name) inside our map
				// it looks like our sequence has items each of them is map 
				// with only one pair commandName: commandBody
				// 
				if (!fakeCommand->IsMap() || fakeCommand->size() != 1)
					return false;
				auto command = fakeCommand->begin();

				const string commandType = command->first.Scalar();
				auto actualCommand = parseCommandByType(command->second, commandType);
				commands.push_back(actualCommand);
			}
			session.commands = commands;
		}

		return true;
	}

	// 
	CONVERTER_DECODE(ReplaceMethodRVACommand *, node, command)
	{
		assertIsMap(node);
		auto value = new ReplaceMethodRVACommand();


		value->Target = readMemberPath("Target", node);
		value->Source = readMemberPath("Source", node);

		command = value;

		return true;
	}
}
