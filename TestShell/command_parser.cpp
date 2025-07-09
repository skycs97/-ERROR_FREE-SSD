#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "command_parser.h"
#include "command_list.h"
#include "command_factory.h"
#include "TEST_SHELL_CONFIG.h"

using std::string;

std::shared_ptr<Command> CommandParser::parseAndMakeShellCommand(const std::string& userInputCommand)
{
	auto splited_cmd = splitCmd(userInputCommand);
	string cmdName = splited_cmd.first;
	vector<string> args = splited_cmd.second;

	auto cmd = makeCommand(cmdName, args);

	if (cmd == nullptr)
		throw TestScriptFailExcpetion("Invalid command");;
		throw std::invalid_argument("Invalid command");
	if (cmd->getNumOfArgs() != args.size())
		throw std::invalid_argument("invliad arguments");

	return cmd;
}

std::pair<string, vector<string>> CommandParser::splitCmd(const std::string& userInputCommand)
{
	std::istringstream ss(userInputCommand);
	std::string word;
	std::vector<std::string> args;

	if (cmd->getShellCommands().size() != cmd->getNumOfArgs())
		throw TestScriptFailExcpetion("Invalid command");;
	ss >> word;
	string cmdName = convertShortCommand(word);

	while (ss >> word) {
		args.push_back(word);
	}

	return std::make_pair(cmdName, args);
}

std::shared_ptr<Command> CommandParser::makeCommand(const std::string& cmdName, const std::vector<std::string>& args)
{
	return factoryComplex.makeCommand(cmdName, args);
}

bool CommandParser::isShortedCommand(const std::string cmdName) {
	if (shortCommandToCommand.find(cmdName) != shortCommandToCommand.end()) {
		return true;
	}

	return false;
}
std::string CommandParser::convertShortCommand(const std::string cmdName) {
	if (isShortedCommand(cmdName)) {
		return shortCommandToCommand.at(cmdName);
	}
	return cmdName;
}