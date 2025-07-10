#include "full_write_command.h"

namespace {
	const int numOfArgs = 1;
};

FullWriteCommand::FullWriteCommand(const std::vector<std::string>& args) : Command(CMD_FULLWRITE, ::numOfArgs)
{
	value = args[0];
}

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	string writeResult;
	string fullWriteResult = "";

	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		writeResult = cmdRunner.write(std::to_string(lba), this->value);
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

std::shared_ptr<Command> FullWriteCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::shared_ptr<FullWriteCommand>(new FullWriteCommand(args));
}
