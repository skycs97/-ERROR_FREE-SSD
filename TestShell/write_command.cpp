#include "write_command.h"
#include <iostream>

void WriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
}

void WriteCommand::printHelp() const
{
	std::cout << "** Write Command **\n";
	std::cout << " - Writes value to the specified LBA of SSD.\n\n";
	std::cout << "Usage\n";
	std::cout << " write [LBA] [value]\n";
	std::cout << "Example\n";
	std::cout << " write 0 0xAAAABBBBB\n";
	std::cout << " write 10 0x10002000\n";
}

