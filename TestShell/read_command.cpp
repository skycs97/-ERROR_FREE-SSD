#include "read_command.h"
#include <iostream>

void ReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.read(ShellCommands[1]));
}

void ReadCommand::printHelp() const
{
	std::cout << "** Read Command **\n";
	std::cout << " - Reads data from the specified LBA from SSD.\n\n";
	std::cout << "Usage\n";
	std::cout << " read [LBA]\n";
	std::cout << "Example\n";
	std::cout << " read 0\n";
	std::cout << " read 10\n";
}
