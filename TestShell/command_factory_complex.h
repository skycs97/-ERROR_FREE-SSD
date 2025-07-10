#pragma once
#include "command_list.h"

class CommandFactoryComplex {
public:
	void addFactory(const string& cmdName, CommandFactory* factory);
	CommandFactory* getFactory(const string& cmdName);
	std::shared_ptr<Command> makeCommand(const string& cmdName, const vector<string>& args);
private:
	std::map<string, CommandFactory*> factoryComplex;
};