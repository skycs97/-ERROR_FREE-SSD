#pragma once
#include "command.h"
#include <map>

class CommandFactory {
public:
	virtual std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) = 0;
};