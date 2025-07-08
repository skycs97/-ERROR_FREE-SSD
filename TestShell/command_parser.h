#pragma once
#include <iostream>
#include "command_list.h"

class CommandParser {

public:
	Command* getCommand(const std::string& command);
};