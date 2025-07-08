#include "exit_command.h"
#include <iostream>

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
