#pragma once
#include <iostream>
#include <vector>
#include "command_runner.h"

namespace {
	const std::string CMD_READ = "read";
	const std::string CMD_WRITE = "write";
	const std::string CMD_EXIT = "exit";
	const std::string CMD_HELP = "help";
	const std::string CMD_FULLWRITE = "fullwrite";
	const std::string CMD_FULLREAD = "fullread";
	const std::string CMD_1_FULLWRITEANDREADCOMPARE = "1_FullWriteAndReadCompare";
	const std::string CMD_1_ = "1_";
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

class ReadCommand : public Command {
public:
	ReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 2;
		help = "read [LBA]";
	};

	void run(const CommandRunner& cmdRunner) const override;
};

class WriteCommand : public Command {
public:

	WriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 3;
		help = "write [LBA] [data]";
	};

	void run(const CommandRunner& cmdRunner) const override;
};

class ExitCommand : public Command {
public:

	ExitCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "exit";
	};

	void run(const CommandRunner& cmdRunner) const override;
};

class HelpCommand : public Command {
public:

	HelpCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "help";
	};

	void run(const CommandRunner& cmdRunner) const override;
};

class FullWriteCommand : public Command {
public:

	FullWriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "fullwrite";
	};

	void run(const CommandRunner& cmdRunner) const override;
};

class FullReadCommand : public Command {
public:

	FullReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "fullread";
	};

	void run(const CommandRunner& cmdRunner) const override;
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
