#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "command_parser.h"
#include "command.h"

using std::vector;
using std::string;
using std::ifstream;

class TestShell {
public:

	static TestShell& getShell() {
		static TestShell instance;
		return instance;
	}

	void runShell(int argc, char* argv[]);

private:
	void startShellLoop();

	void printTestResult(const string& result);
	void runShellScript(const string& input);

	bool parseAndRunCommand(const string& input);
	void runShellCommand(std::shared_ptr<Command> command);
	bool isRunShellScript(int argc);
	bool isEmptyInput(const string& input);
	bool isFileOpenFail(const ifstream& inputFile);

	string getUserInput();

	TestShell();
	TestShell& operator=(const TestShell& other) = delete;
	TestShell(const TestShell& other) = delete;

	CommandRunner runner;
	CommandParser parser;
};
