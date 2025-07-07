#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "command_parser.h"

using std::vector;
using std::string;


class TestShell {
public:
	void runShell();
	void HelpCommand();

private:
	vector<std::string> command;
	CommandParser parser;
};
