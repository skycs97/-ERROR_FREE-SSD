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
	CommandRunner runner;

	static TestShell& getShell() {
		static TestShell instance;
		return instance;
	}

	void runShell(int argc, char* argv[]);

private:
	void runShellScript(const string& input);
	void printTestResult(const string& result);
	void printTestProcess(const string& command);

	bool parseAndRunCommand(const string& input);
	bool isFilePathExist(int argc);
	bool isEmptyInput(const string& input);
	bool isFileOpenFail(const ifstream& inputFile);

	string getUserInput();

	TestShell() {};
	TestShell& operator=(const TestShell& other) = delete;
	TestShell(const TestShell& other) = delete;

	Command* command = nullptr;
	CommandParser parser;
};
