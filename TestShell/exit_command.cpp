#include <iostream>
#include "exit_command.h"

namespace {
	const int numOfArgs = 0;
}

ExitCommand::ExitCommand(const std::vector<std::string>& args) : Command(CMD_EXIT, ::numOfArgs)
{
}

void ExitCommand::run(const CommandRunner& cmdRunner) const
{
	exit(0);
}

void ExitCommand::printHelp() const
{
	std::cout << "** Exit Shell Command **\n";
	std::cout << " - Exit Test Shell .\n";
	std::cout << "Usage\n";
	std::cout << " exit\n";
}

std::shared_ptr<Command> ExitCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::shared_ptr<ExitCommand>(new ExitCommand(args));
}
