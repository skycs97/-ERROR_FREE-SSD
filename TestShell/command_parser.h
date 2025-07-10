#pragma once
#include <iostream>
#include "command_factory_complex.h"

class CommandParser {
public:
	CommandParser();
	std::shared_ptr<Command> parseAndMakeShellCommand(const std::string& userInputCommand);
private:
	std::pair<string, vector<string>> splitCmd(const std::string& command);
	std::shared_ptr<Command> makeCommand(const std::string& cmdName, const std::vector<std::string>& args);
	bool isShortedCommand(const std::string cmdName);
	std::string convertShortCommand(const std::string cmdName);

	void initCommandList();
	void registCommand(const std::string& cmdName, CommandInfo cmdInfo);
	
	CommandFactoryComplex factoryComplex;
};