#pragma once
#include <iostream>
#include "command_factory_complex.h"

class CommandParser {
public:
	std::shared_ptr<Command> parseAndMakeShellCommand(const std::string& userInputCommand);
private:
	std::pair<string, vector<string>> splitCmd(const std::string& command);
	std::shared_ptr<Command> makeCommand(const std::string& cmdName, const std::vector<std::string>& args);
	CommandFactoryComplex factoryComplex;
};