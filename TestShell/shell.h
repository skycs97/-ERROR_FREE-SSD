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
	static TestShell& getShell() {
		static TestShell instance;
		return instance;
	}

	void runShell();
	void HelpCommand();

private:
	TestShell() {};
	TestShell& operator=(const TestShell& other) = delete;
	TestShell(const TestShell& other) = delete;
	vector<std::string> command;
	CommandParser parser;
};
