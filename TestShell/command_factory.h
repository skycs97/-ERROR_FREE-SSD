#pragma once
#include "command_list.h"

class FactoryCommand {
public:
	Command* makeCommand(const std::string& cmd);
};
