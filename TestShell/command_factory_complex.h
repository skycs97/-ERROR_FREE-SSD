#pragma once
#include "command_list.h"

class CommandFactoryComplex {
public:
	CommandFactoryComplex() {
		addFactory(CMD_HELP, new HelpCommandFactory());
		addFactory(CMD_READ, new ReadCommandFactory());
		addFactory(CMD_ERASE, new EraseCommandFactory());
		addFactory(CMD_ERASE_RANGE, new EraseRangeCommandFactory());
		addFactory(CMD_WRITE, new WriteCommandFactory());
		addFactory(CMD_EXIT, new ExitCommandFactory());
		addFactory(CMD_FULLREAD, new FullReadCommandFactory());
		addFactory(CMD_FULLWRITE, new FullWriteCommandFactory());
		addFactory(CMD_FLUSH, new FlushCommandFactory());
		addFactory(CMD_1_FULL_WRITE_AND_READ_COMPARE, new FullWriteAndReadCompareCommandFactory());
		addFactory(CMD_2_PARTIAL_LBA_WRITE, new PartialLBAWriteCommandFactory());
		addFactory(CMD_3_WRITE_READ_AGING, new WriteReadAgingCommandFactory());
	}
	void addFactory(const string& cmdName, CommandFactory* factory);
	CommandFactory* getFactory(const string& cmdName);
	std::shared_ptr<Command> makeCommand(const string& cmdName, const vector<string>& args);
private:
	std::map<string, CommandFactory*> factoryComplex;
};