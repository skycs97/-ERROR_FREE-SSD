#pragma once
#include <iostream>
#include <vector>
#include "command_runner.h"
#include "TEST_SHELL_CONFIG.h"

namespace {
	const std::string CMD_READ = "read";
	const std::string CMD_WRITE = "write";
	const std::string CMD_EXIT = "exit";
	const std::string CMD_HELP = "help";
	const std::string CMD_FULLWRITE = "fullwrite";
	const std::string CMD_FULLREAD = "fullread";
	const std::string CMD_1_FULLWRITEANDREADCOMPARE = "1_FullWriteAndReadCompare";
	const std::string CMD_1_ = "1_";
	const std::string CMD_2_PartialLBAWrite = "2_PartialLBAWrite";
	const std::string CMD_2_ = "2_";
    const std::string CMD_3_WRITEREADAGING = "3_WriteReadAging";
	const std::string CMD_3_ = "3_";
	const std::string ERROR = "ERROR";
	const std::string DONE = "DONE";
}

class Command {
public:
	Command(std::vector<std::string> commands);
	std::vector<std::string> getShellCommands(void);
	std::string getHelp(void) const;
	int getNumOfArgs(void);

	virtual void run(const CommandRunner& cmdRunner) const = 0;

	std::vector<std::string> ShellCommands;

	int numOfArgs = 0;
	std::string help = "";

protected:
	static const int MAX_ADDR = 99;
	static const int MIN_ADDR = 0;
};

class FullWriteAndReadCompare : public Command {
public:
	FullWriteAndReadCompare(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "FullWriteAndReadCompare";
	};
	void run(const CommandRunner& cmdRunner) const override;
};

class PartialLBAWrite : public Command {
public:
	PartialLBAWrite(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "PartialLBAWrite";
	};
	void run(const CommandRunner& cmdRunner) const override;
private:
	static const int REPEAT_COUNT = 30;
	const std::string WRITE_DATA{ "0x12341234" };
	std::vector<std::string> TestLbaList = { "4","0","3","1","2" };

	bool checkResult(const std::vector<std::string>& result) const;
};

class WriteReadAging : public Command {
public:
	WriteReadAging(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 0;
		help = "WriteReadAging";
	};
	void run(const CommandRunner& cmdRunner) const override;
};

class FactoryCommand {
public:
	Command* makeCommand(const std::string& cmd);
};
