#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "command_parser.h"
#include "command.h"

using std::vector;
using std::string;

class TestShell {
public:
	static TestShell& getShell() {
		static TestShell instance;
		return instance;
	}

	void runShell();

private:
	bool isEmptyInput(const string& input);
	string getUserInput();

	TestShell() {};
	TestShell& operator=(const TestShell& other) = delete;
	TestShell(const TestShell& other) = delete;

	Command* command = nullptr;
	CommandParser parser;
};
