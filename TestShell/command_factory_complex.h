#pragma once
#include "command_list.h"
namespace {
	//std::map<string, CommandFactory> factoryComplex = {
	//	{CMD_HELP, HelpCommandFactory},
	//	//{CMD_READ, ReadCommandFactory()},
	//	//{CMD_WRITE, new WriteCommandFactory()},
	//	//{CMD_EXIT, new ExitCommandFactory()},
	//	//{CMD_FULLREAD, new FullReadCommandFactory()},
	//	//{CMD_FULLWRITE, new FullWriteCommandFactory()},
	//	//{CMD_1_FULL_WRITE_AND_READ_COMPARE, new FullWriteAndReadCompareCommandFactory()},
	//	//{CMD_2_PARTIAL_LBA_WRITE, new PartialLBAWriteCommandFactory()},
	//	//{CMD_3_WRITE_READ_AGING, new WriteReadAgingCommandFactory()}
	//};
};

class CommandFactoryComplex {
public:
	CommandFactoryComplex() {
		/*for (auto cmdName : AVAILABLE_COMMAND_LIST) {
			if (::factoryComplex.find(cmdName) != ::factoryComplex.end()) {
				addFactory(cmdName, new (::factoryComplex[cmdName])());
			}
		}*/
		addFactory(CMD_HELP, new HelpCommandFactory());
		addFactory(CMD_READ, new ReadCommandFactory());
		addFactory(CMD_WRITE, new WriteCommandFactory());
		addFactory(CMD_EXIT, new ExitCommandFactory());
		addFactory(CMD_FULLREAD, new FullReadCommandFactory());
		addFactory(CMD_FULLWRITE, new FullWriteCommandFactory());
		addFactory(CMD_1_FULL_WRITE_AND_READ_COMPARE, new FullWriteAndReadCompareCommandFactory());
		addFactory(CMD_2_PARTIAL_LBA_WRITE, new PartialLBAWriteCommandFactory());
		addFactory(CMD_3_WRITE_READ_AGING, new WriteReadAgingCommandFactory());
	}
	void addFactory(const string& cmdName, CommandFactory* factory);
	CommandFactory* getFactory(const string& cmdName);
private:
	std::map<string, CommandFactory*> factoryComplex;
};