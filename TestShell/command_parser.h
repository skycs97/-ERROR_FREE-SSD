#pragma once
#include <iostream>
#include <vector>

class CommandParser {

public:
	std::vector<std::string> getCommand(const std::string& command);
};