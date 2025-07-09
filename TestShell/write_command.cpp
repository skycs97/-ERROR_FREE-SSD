#include <iostream>
#include "write_command.h"

void WriteCommand::run(const CommandRunner& cmdRunner) const
{
	string result = cmdRunner.write(ShellCommands[1], ShellCommands[2]);
	printResult(result);
}

void WriteCommand::printResult(const string& result) const
{
	std::cout << "[Write] ";
	if (result == "")
		std::cout << DONE;
	else
		std::cout << ERROR;

	std::cout << std::endl << std::endl;
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

