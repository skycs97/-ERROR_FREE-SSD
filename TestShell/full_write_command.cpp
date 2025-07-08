#include "full_write_command.h"

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
	}
}

void FullWriteCommand::printHelp() const
{
	std::cout << "** Full Write Command **\n";
	std::cout << " - Writes value to the all LBAs in SSD.\n";
	std::cout << " - LBA (" << MIN_LBA << " ~ " << MAX_LBA << ")\n\n";
	std::cout << "Usage\n";
	std::cout << " fullwrite [value]\n";
	std::cout << "Example\n";
	std::cout << " fullwrite 0xAAAABBBBB\n";
	std::cout << " fullwrite 0x10002000\n";
}
