#include "full_read_command.h"

void FullReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		result.push_back(cmdRunner.read(ShellCommands[1]));
	}
}

void FullReadCommand::printHelp() const
{
	std::cout << "** Full Read Command **\n";
	std::cout << " - Read value from the all LBAs in SSD.\n";
	std::cout << " - LBA (" << MIN_LBA << " ~ " << MAX_LBA << ")\n\n";
	std::cout << "Usage\n";
	std::cout << " fullread\n";
}
