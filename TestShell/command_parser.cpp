#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "command_parser.h"
#include "command.h"
using std::string;

Command* CommandParser::getCommand(const std::string& command)
{
	FactoryCommand fc;
	Command* cmd = fc.makeCommand(command);

	if (cmd == nullptr)
		throw std::invalid_argument("Invalid command");

	if (cmd->getShellCommands().size() != cmd->getNumOfArgs())
		throw std::invalid_argument("Invalid argument");

	return cmd;
}
