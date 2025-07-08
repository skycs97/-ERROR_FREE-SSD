#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "command.h"
#include "command_runner.h"

Command::Command(std::vector<std::string> commands) : ShellCommands(commands)
{
}

std::vector<std::string> Command::getShellCommands(void) {
	return ShellCommands;
}

std::string Command::getHelp(void) const {
	return help;
}

int Command::getNumOfArgs(void) {
	return numOfArgs;
}

void ReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.read(ShellCommands[1]));
}

void WriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
}

void ExitCommand::run(const CommandRunner& cmdRunner) const
{
	exit(0);
}

void HelpCommand::run(const CommandRunner& cmdRunner) const
{
	std::cout << getHelp();
}

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_ADDR; lba <= MAX_ADDR; lba++) {
		result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
	}
}

void FullReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_ADDR; lba <= MAX_ADDR; lba++) {
		result.push_back(cmdRunner.read(ShellCommands[1]));
	}
}
void FullWriteAndReadCompare::run(const CommandRunner& cmdRunner) const
{
}

void PartialLBAWrite::run(const CommandRunner& cmdRunner) const
{
}

void WriteReadAging::run(const CommandRunner& cmdRunner) const
{
}

Command* FactoryCommand::makeCommand(const std::string& cmd)
{
	std::istringstream ss(cmd);
	std::string word;
	std::vector<std::string> commands;
	std::string shellCmd;

	while (ss >> word) {
		commands.push_back(word);
	}

	shellCmd = commands.front();

	if (shellCmd == CMD_READ) return new ReadCommand(commands);
	else if (shellCmd == CMD_WRITE) return new WriteCommand(commands);
	else if (shellCmd == CMD_EXIT) return new ExitCommand(commands);
	else if (shellCmd == CMD_HELP) return new HelpCommand(commands);
	else if (shellCmd == CMD_FULLWRITE) return new FullWriteCommand(commands);
	else if (shellCmd == CMD_FULLREAD) return new FullReadCommand(commands);

	else return nullptr;
}