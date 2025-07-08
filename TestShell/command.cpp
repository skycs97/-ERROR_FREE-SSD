#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "command.h"

Command::Command(std::vector<std::string> commands) {

	ShellCommands = commands;
}

std::vector<std::string> Command::getShellCommands(void) {
	return ShellCommands;
}

std::string Command::getHelp(void) {
	return help;
}

int Command::getNumOfArgs(void) {
	return numOfArgs;
}

void ReadCommand::run(void)
{
}

void WriteCommand::run(void)
{
}

void ExitCommand::run(void)
{
}

void HelpCommand::run(void)
{
}

void FullWriteCommand::run(void)
{
}

void FullReadCommand::run(void)
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