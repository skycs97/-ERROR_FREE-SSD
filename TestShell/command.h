#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <random>
#include "command_runner.h"
#include "TEST_SHELL_CONFIG.h"
#include "test_util.h"

class Command {
public:
	Command(const string& cmdName, const int numOfArgs);
	int getNumOfArgs(void);
	string getCmdName(void);
	void printProcess(void) const;

	virtual void run(const CommandRunner& cmdRunner) const = 0;
	virtual void printHelp(void) const = 0;
protected:
	int numOfArgs;
	string cmdName;
};

class TestScriptFailExcpetion : public std::exception {
public:
	TestScriptFailExcpetion(const std::string& msg) : message(msg) {};
	const char* what() const noexcept override {
		return message.c_str();
	}
private:
	std::string message;
};