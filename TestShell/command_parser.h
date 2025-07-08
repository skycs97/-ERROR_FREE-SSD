#pragma once
#include <iostream>
#include "command.h"

class CommandParser {

public:
	Command* getCommand(const std::string& command);
};