#include <iostream>
#include "exit_command.h"
#include "logger.h"

namespace {
	const int numOfArgs = 0;
}

ExitCommand::ExitCommand(const std::vector<std::string>& args) : Command(CMD_EXIT, ::numOfArgs)
{
}

void ExitCommand::run(const CommandRunner& cmdRunner) const
{
	LOGGING_SHELL( "");
	exit(0);
}

std::shared_ptr<Command> ExitCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_EXIT) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<ExitCommand>(new ExitCommand(args));
}
