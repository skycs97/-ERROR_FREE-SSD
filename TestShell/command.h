#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "command_runner.h"
#include "TEST_SHELL_CONFIG.h"

class Command {
public:
	Command(std::vector<std::string> commands);
	std::vector<std::string> getShellCommands(void);
	int getNumOfArgs(void);

	virtual void run(const CommandRunner& cmdRunner) const = 0;
	virtual void printHelp(void) const = 0;

	std::vector<std::string> ShellCommands;

	int numOfArgs = 0;
};

class TestScriptFailExcpetion : public std::exception {
public:
	const char* what() const noexcept override {
		return "FAIL!";
	}
};