#pragma once
#include <iostream>
#include <vector>

namespace {
	const std::string CMD_READ = "read";
	const std::string CMD_WRITE = "write";
	const std::string CMD_EXIT = "exit";
	const std::string CMD_HELP = "help";
	const std::string CMD_FULLWRITE = "fullwrite";
	const std::string CMD_FULLREAD = "fullread";
}

class Command {
public:
	Command(std::vector<std::string> commands);
	std::vector<std::string> getShellCommands(void);
	std::string getHelp(void);
	int getNumOfArgs(void);

	virtual void run(void) = 0;

	std::vector<std::string> ShellCommands;
	int numOfArgs = 0;
	std::string help = "";
};

class ReadCommand : public Command {
public:
	ReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 2;
		help = "read [LBA]";
	};
	void run(void) override;
};

class WriteCommand : public Command {
public:
	WriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 3;
		help = "write [LBA] [data]";
	};
	void run(void) override;
};

class ExitCommand : public Command {
public:
	ExitCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "exit";
	};
	void run(void) override;
};

class HelpCommand : public Command {
public:
	HelpCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "help";
	};
	void run(void) override;
};

class FullWriteCommand : public Command {
public:
	FullWriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "fullwrite";
	};
	void run(void) override;
};

class FullReadCommand : public Command {
public:
	FullReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "fullread";
	};
	void run(void) override;
};

class FactoryCommand {
public:
	Command* makeCommand(const std::string& cmd);
};
