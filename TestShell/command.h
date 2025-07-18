#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <random>
#include <system_error>
#include "command_runner.h"
#include "TEST_SHELL_CONFIG.h"
#include "test_util.h"

class Command {
public:
	Command(const string& cmdName, const int numOfArgs);
	int getNumOfArgs(void);
	string getCmdName(void);
	void printProcess(void) const;
	void printPass(void) const;

	virtual void run(const CommandRunner& cmdRunner) const = 0;
protected:
	int numOfArgs;
	string cmdName;
	bool isValidLba(int lba) const;
};

class CommandRunFailException : public std::exception {
public:
	CommandRunFailException(const std::string& msg) : message(msg) {};
	const char* what() const noexcept override {
		return message.c_str();
	}
private:
	std::string message;
};