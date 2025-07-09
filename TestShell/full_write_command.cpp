#include "full_write_command.h"

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	string writeResult;
	string fullWriteResult = "";

	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		writeResult = cmdRunner.write(std::to_string(lba), ShellCommands[1]);
		if (writeResult == ERROR)
			fullWriteResult = ERROR;
	}

	printResult(fullWriteResult);
}

void FullWriteCommand::printResult(const string& result) const
{
	std::cout << "[Full Write] ";
	if (result == "")
		std::cout << DONE;
	else
		std::cout << ERROR;

	std::cout << std::endl << std::endl;
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
