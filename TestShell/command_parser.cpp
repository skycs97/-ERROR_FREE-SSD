#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "command_parser.h"
#include "command_list.h"
#include "command_factory.h"

using std::string;

Command* CommandParser::getCommand(const std::string& command)
{
	FactoryCommand fc;
	Command* cmd = fc.makeCommand(command);

	if (cmd == nullptr)
		throw TestScriptFailExcpetion("Invalid command");;

	if (cmd->getShellCommands().size() != cmd->getNumOfArgs())
		throw TestScriptFailExcpetion("Invalid command");;

	return cmd;
}
