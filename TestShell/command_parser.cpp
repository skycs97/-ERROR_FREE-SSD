#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "command_parser.h"
#include "TEST_SHELL_CONFIG.h"
#include "helper.h"

using std::string;

std::shared_ptr<Command> CommandParser::parseAndMakeShellCommand(const std::string& userInputCommand)
{
	auto splited_cmd = splitCmd(userInputCommand);
	string cmdName = splited_cmd.first;
	vector<string> args = splited_cmd.second;

	auto cmd = makeCommand(cmdName, args);

	if (cmd == nullptr) {
		if (find(AVAILABLE_COMMAND_LIST.begin(), AVAILABLE_COMMAND_LIST.end(), cmdName)
			!= AVAILABLE_COMMAND_LIST.end()) {
			Helper::printCmdHelp(cmdName);
			throw std::invalid_argument("");
		}
		else {
			throw std::invalid_argument("Invalid command");
		}
	}

	return cmd;
}

std::pair<string, vector<string>> CommandParser::splitCmd(const std::string& userInputCommand)
{
	std::istringstream ss(userInputCommand);
	std::string word;
	std::vector<std::string> args;

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

void CommandParser::registCommand(const std::string& cmdName, CommandInfo cmdInfo)
{
	Helper::registerCmd(cmdName, cmdInfo.helpStr);
	factoryComplex.addFactory(cmdName, cmdInfo.factory);
}

void CommandParser::initCommandList() {
	for (auto cmdItem : cmdList) {
		registCommand(cmdItem.first, cmdItem.second);
	}
}

CommandParser::CommandParser()
{
	initCommandList();
}